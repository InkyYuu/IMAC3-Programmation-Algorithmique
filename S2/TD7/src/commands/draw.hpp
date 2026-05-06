#pragma once

#include "osm/data.hpp"
#include "osm/positionedGraph.hpp"
#include "raylib.h"
#include <glm/glm.hpp>
#include <optional>


struct DijkstraResult {
    std::vector<OSM::NodeId> path;
};
struct DrawingContext {
    Camera2D camera;
    const PositionedGraph& graph;

    OSM::NodeId nearest_NodeId {};
    std::optional<OSM::NodeId> hovered_NodeId {};
    std::optional<OSM::NodeId> selected_NodeId {};
    std::optional<DijkstraResult> dijkstra_result {};
};

void draw_loop(const PositionedGraph& graph);
