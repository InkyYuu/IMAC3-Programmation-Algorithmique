#pragma once

#include "glm/ext/vector_float2.hpp"
#include <string>
#include <vector>

namespace OSM {
    // node identifier use 64 bits integer (https://wiki.openstreetmap.org/wiki/64-bit_Identifiers)
    using NodeId = uint64_t;

    struct Node {
        NodeId id {};
        glm::vec2 coordinates {}; // (lat, lon)
    };

    struct Way {
        NodeId id {};
        std::vector<NodeId> node_ids {};
        std::vector<std::pair<std::string, std::string>> tags {};
    };

    struct Bounds {
        glm::vec2 min {}; // (minlat, minlon)
        glm::vec2 max {}; // (maxlat, maxlon)

        inline glm::vec2 size() const { return max - min; }
        inline bool contains(glm::vec2 const& coord) const {
            return (coord.x >= min.x && coord.x <= max.x &&
                    coord.y >= min.y && coord.y <= max.y);
        }
    };
}
