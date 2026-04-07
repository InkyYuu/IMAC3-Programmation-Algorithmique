#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string>
#include <unordered_set>

/* Q1 */
/*
  On se donne comme convention que la position (0, 0) est en haut à gauche de la
  carte. La position (0, 1) est juste en dessous de la position (0, 0) et la
  position (1, 0) est juste à droite de la position (0, 0).

  Les directions sont représentées comme suit :
  - `Direction::Haut` correspond à (0, -1)
  - `Direction::Droite` correspond à (1, 0)
  - `Direction::Bas` correspond à (0, 1)
  - `Direction::Gauche` correspond à (-1, 0)
*/

enum class Direction { Haut, Bas, Gauche, Droite };
struct Position {
  int x;
  int y;
};

bool operator==(const Position &a, const Position &b) {
  return a.x == b.x && a.y == b.y;
}

std::ostream &operator<<(std::ostream &os, const Position &pos) {
  os << "(" << pos.x << ", " << pos.y << ")";
  return os;
}

void operator+=(Position &pos, Position &delta) {
  pos.x += delta.x;
  pos.y += delta.y;
}

Position operator+(Position &pos, Direction &dir) {
  Position result = pos;
  switch (dir) {
  case Direction::Haut:
    result.y -= 1;
    break;
  case Direction::Bas:
    result.y += 1;
    break;
  case Direction::Gauche:
    result.x -= 1;
    break;
  case Direction::Droite:
    result.x += 1;
    break;
  }
  return result;
}

void operator+=(Position &pos, Direction dir) { pos = pos + dir; }

Direction turn_right(Direction dir) {
  switch (dir) {
  case Direction::Haut:
    return Direction::Droite;
  case Direction::Droite:
    return Direction::Bas;
  case Direction::Bas:
    return Direction::Gauche;
  case Direction::Gauche:
    return Direction::Haut;
  }
  return dir;
}

/* Q2 */
/*
  On note :
  . représente une case vide
  # représente un obstacle
  ^, >, v, < représentent la position du garde et la direction dans laquelle il
  regarde (haut, droite, bas, gauche).
*/

namespace std {
template <> struct hash<Position> {
  std::size_t operator()(const Position &pos) const {
    std::size_t hashCode = 31;
    return pos.x * hashCode + pos.y;
  }
};
} // namespace std

struct Input_Map {
  std::unordered_set<Position> obstacles{};
  Position guard_position{};
  Direction guard_direction{};
  int width;
  int height;
};

void char_to_direction(char c, Direction &dir) {
  switch (c) {
  case '^':
    dir = Direction::Haut;
    break;
  case '>':
    dir = Direction::Droite;
    break;
  case 'v':
    dir = Direction::Bas;
    break;
  case '<':
    dir = Direction::Gauche;
    break;
  }
}

std::string to_string(Direction dir) {
  switch (dir) {
  case Direction::Haut:
    return "Haut";
  case Direction::Droite:
    return "Droite";
  case Direction::Bas:
    return "Bas";
  case Direction::Gauche:
    return "Gauche";
  }
  return "Inconnu";
}

/**
 * Parse l'entrée de la carte à partir d'un flux d'entrée.
 * @param input_stream le flux d'entrée contenant la carte
 * @return une structure Input_Map contenant les informations de la carte, y
 * compris les positions des obstacles, la position et la direction du garde,
 * ainsi que les dimensions de la carte.
 */
Input_Map parse_input(std::istream &input_stream) {
  Input_Map map;

  size_t row{0};
  size_t col{0};
  for (std::string line{};
       std::getline(input_stream, line, '\n') and line != "";) {
    for (col = 0; col < line.size(); ++col) {
      char c = line[col];
      if (c == '#') {
        map.obstacles.insert({static_cast<int>(col), static_cast<int>(row)});
      } else if (c == '^' || c == '>' || c == 'v' || c == '<') {
        map.guard_position = {static_cast<int>(col), static_cast<int>(row)};
        char_to_direction(c, map.guard_direction);
      }
    }
    ++row;
  }
  map.width = static_cast<int>(col);
  map.height = static_cast<int>(row);
  return map;
}

struct GuardState {
  Position position;
  Direction direction;
};

bool operator==(const GuardState &a, const GuardState &b) {
  return a.position == b.position && a.direction == b.direction;
}

namespace std {
template <> struct hash<GuardState> {
  std::size_t operator()(const GuardState &state) const {
    std::size_t hashCode = 31;
    return state.position.x * hashCode + state.position.y;
  }
};
} // namespace std

/* Q3 */
struct WalkResult {
  Position final_position;
  size_t steps_taken;
  std::unordered_set<GuardState> guard_states_visited;
};

/**
 * Simule la marche du garde sur la carte.
 * Le garde avance d'une case dans la direction dans laquelle il regarde. S'il
 * rencontre un obstacle, il tourne à droite et essaie à nouveau. S'il sort de
 * la carte, la simulation s'arrête.
 * Si le garde revient à un état déjà visité (même position et même direction),
 * la simulation s'arrête également pour éviter les cycles infinis.
 * @param map la carte d'entrée
 * @return le résultat de la simulation, incluant la position finale du garde,
 * le nombre de pas effectués, et les états du garde visités pendant la
 * simulation.
 */
WalkResult walk_simulation(Input_Map map) {
  WalkResult result;
  Position current_position = map.guard_position;
  Direction current_direction = map.guard_direction;
  GuardState initial_state{current_position, current_direction};
  std::unordered_set<GuardState> guard_states_visited = {initial_state};
  size_t steps_taken = 0;

  while (true) {
    Position next_position = current_position + current_direction;

    // Si on sort de la carte on arrête la simulation
    if (next_position.x < 0 || next_position.x >= map.width ||
        next_position.y < 0 || next_position.y >= map.height) {
      break;
    }

    /* Q4 */
    // Si on revient à un état déjà visité, on arrête la simulation
    if (guard_states_visited.find({next_position, current_direction}) !=
        guard_states_visited.end()) {
      std::cout << "Cycle detected ! Ending simulation.\n";
      for (const auto &state : guard_states_visited) {
        std::cout << "Visited state: position " << state.position << "\n";
      }
      break;
    }

    // Si on rencontre un obstacle, on tourne à droite et on essaie à nouveau
    if (map.obstacles.count(next_position) > 0) {
      current_direction = turn_right(current_direction);
      continue;
    }

    // Sinon, on avance
    current_position = next_position;
    guard_states_visited.insert({current_position, current_direction});
    steps_taken++;
  }

  result.final_position = current_position;
  result.steps_taken = steps_taken;
  result.guard_states_visited = guard_states_visited;
  return result;
}

int main() {
  std::cout << "Enter the map (end with an empty line):\n";
  Input_Map map = parse_input(std::cin);
  std::cout << "Width: " << map.width << ", Height: " << map.height << "\n";
  std::cout << "Guard position: " << map.guard_position
            << ", direction: " << to_string(map.guard_direction) << "\n";
  WalkResult result = walk_simulation(map);
  std::cout << "Final position: " << result.final_position << "\n";
  std::cout << "Steps taken: " << result.steps_taken << "\n";
  std::cout << "Number of visited guard states: "
            << result.guard_states_visited.size() << "\n";
}