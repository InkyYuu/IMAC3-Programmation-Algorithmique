#include "draw.hpp"

#include "raylib.h"

#include <algorithm>
#include <array>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp> // for distance2

#include "dataStructure/graphUtils.hpp"
#include "utils/raylibUtils.hpp"


void handle_inputs(DrawingContext &context) {
  Camera2D &camera{context.camera};
  // update scale with wheel
  // Uses log scaling to provide consistent zoom speed
  camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));
  camera.zoom = std::clamp(camera.zoom, 0.1f, 10.0f);

  // Pan with ctrl + left mouse button
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL)) {
    Vector2 delta = GetMouseDelta();
    camera.target.x -= delta.x / camera.zoom;
    camera.target.y -= delta.y / camera.zoom;
  }

  glm::vec2 world_position{
      glm_vec_from(GetScreenToWorld2D(GetMousePosition(), camera))};

  // Compute nearest node
  float closest_distance_sq = std::numeric_limits<float>::max();
  for (auto const &[node_id, node_position] : context.graph.nodes) {
    const float distance_sq = glm::distance2(world_position, node_position);
    if (distance_sq < closest_distance_sq) {
      closest_distance_sq = distance_sq;
      context.nearest_NodeId = node_id;
    }
  }

  // Compute hovered node
  float const hover_threshold =
      10.0f / camera.zoom; // 10 pixels threshold adjusted for zoom level
  if (closest_distance_sq <= hover_threshold * hover_threshold) {
    context.hovered_NodeId = context.nearest_NodeId;
  } else {
    context.hovered_NodeId.reset();
  }

  // Handle node selection
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      context.hovered_NodeId.has_value()) {
    if (context.selected_NodeId == context.hovered_NodeId) {
      // Deselect if the same node is clicked again
      context.selected_NodeId.reset();
    } else {
      context.selected_NodeId = context.hovered_NodeId;
    }
  }

  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    context.selected_NodeId.reset();
  }

  // Run Dijkstra's algorithm from the selected node to the hovered node (if
  // exists)
  if (IsKeyPressed(KEY_D) && context.selected_NodeId.has_value() &&
      context.hovered_NodeId.has_value()) {
    context.dijkstra_result =
        DijkstraResult{.path = dijkstra_path(context.graph.graph,
                                             context.selected_NodeId.value(),
                                             context.hovered_NodeId.value())};
  }

  if (IsKeyPressed(KEY_C)) {
    context.dijkstra_result.reset();
  }
}

void draw_helper_text(int screenWidth, int screenHeight) {
  // auto deduced type of the std::array
  std::array constexpr sentences{
      "Hold Ctrl + Left Click to Pan",
      "Use Mouse Wheel to Zoom",
      "Click hovered node to select",
      "D to find path (selected to hovered)",
  };
  int constexpr font_size{20};
  int constexpr line_height{font_size + 2}; // add some spacing between lines
  int constexpr padding{10};
  int constexpr sentences_count{static_cast<int>(sentences.size())};

  int max_text_width{0};
  for (auto const &sentence : sentences) {
    max_text_width = std::max(max_text_width, MeasureText(sentence, font_size));
  }

  int const rect_width{max_text_width + padding * 2};
  int const rect_height{(sentences_count - 1) * line_height + font_size +
                        padding * 2};

  // position so the rectangle's outer edge sits `padding` px from the screen
  // corner
  int const posX{screenWidth - rect_width};
  int const posY{screenHeight - rect_height};

  if (IsKeyDown(KEY_H)) {
    // draw background rectangle (with padding)
    DrawRectangle(posX - padding, posY - padding, rect_width, rect_height,
                  Fade(LIGHTGRAY, 0.7f));
    for (int i{0}; i < sentences_count; ++i) {
      DrawText(sentences[i], posX, posY + i * line_height, font_size, DARKGRAY);
    }
  } else {
    DrawText("Press H for Help", posX, posY, font_size, DARKGRAY);
  }
}

void draw_loop(const PositionedGraph &graph) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(1280, 720, "raylib window");

  // Force a regular resizable window state at startup.
  ClearWindowState(FLAG_FULLSCREEN_MODE);
  SetWindowMinSize(800, 450);
  SetTargetFPS(30);

  int const monitor{GetCurrentMonitor()};
  int const monitor_width{GetMonitorWidth(monitor)};
  int const monitor_height{GetMonitorHeight(monitor)};
  if (monitor_width > 0 && monitor_height > 0) {
    SetWindowSize(monitor_width / 2, monitor_height / 2);
    SetWindowPosition(monitor_width / 4, monitor_height / 4);
  }

  DrawingContext context{.camera = {{0.f, 0.f}, {0.f, 0.f}, 0.f, 1.f},
                         .graph = graph};
  int screenWidth{};
  int screenHeight{};

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // update screen size
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    // shift camera to center of the window
    context.camera.offset = {static_cast<float>(screenWidth) / 2.0f,
                             static_cast<float>(screenHeight) / 2.0f};

    handle_inputs(context);

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(context.camera);

    // Draw graph edges
    for (const auto &[a, b, _] : graph.get_edges_list()) {
      const auto &pos_a = graph.node_position(a);
      const auto &pos_b = graph.node_position(b);
      DrawLineV({pos_a.x, pos_a.y}, {pos_b.x, pos_b.y}, BLACK);
    }

    // Draw hovered node
    if (context.hovered_NodeId.has_value()) {
      const auto &hovered_node_pos =
          graph.node_position(context.hovered_NodeId.value());
      DrawCircleV({hovered_node_pos.x, hovered_node_pos.y},
                  10.0f / context.camera.zoom, BLUE);
    }

    // Draw selected node
    if (context.selected_NodeId.has_value()) {
      const auto &selected_node_pos =
          graph.node_position(context.selected_NodeId.value());
      DrawCircleV({selected_node_pos.x, selected_node_pos.y},
                  8.0f / context.camera.zoom, RED);
    }

    // Draw Dijkstra path if exists
    if (context.dijkstra_result.has_value()) {
      std::vector<OSM::NodeId> const &path{context.dijkstra_result->path};
      if (path.size() >= 2) {
        for (size_t i = 0; i < path.size() - 1; ++i) {
          glm::vec2 const &pos_a{graph.node_position(path[i])};
          glm::vec2 const &pos_b{graph.node_position(path[i + 1])};
          DrawLineV({pos_a.x, pos_a.y}, {pos_b.x, pos_b.y}, GREEN);
        }
      }
    }

    EndMode2D();

    // Draw UI text after ending 2D mode so it stays fixed on the screen
    if (context.dijkstra_result.has_value() &&
        context.dijkstra_result->path.size() < 2) {
      DrawText("No path found", 10, 90, 20, ORANGE);
    }

    DrawFPS(10, 10);

    if (context.hovered_NodeId.has_value()) {
      DrawText(
          TextFormat("Hovered Node ID: %d", context.hovered_NodeId.value()), 10,
          30, 20, DARKGRAY);
    } else {
      DrawText("Hovered Node ID: None", 10, 30, 20, DARKGRAY);
    }

    if (context.selected_NodeId.has_value()) {
      DrawText(
          TextFormat("Selected Node ID: %d", context.selected_NodeId.value()),
          10, 60, 20, DARKGRAY);

    } else {
      DrawText("Selected Node ID: None", 10, 60, 20, DARKGRAY);
    }

    // draw helper text a bottom right corner of the screen
    draw_helper_text(screenWidth, screenHeight);

    EndDrawing();
  }
}