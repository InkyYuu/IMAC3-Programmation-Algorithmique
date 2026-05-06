#pragma once

#include <vector>
#include "data.hpp"

namespace OSM {
    void remove_building_ways(std::vector<Way>& ways);
    void remove_railway_ways(std::vector<Way>& ways);
    void keep_way_in_bounds(std::vector<Way>& ways, std::vector<Node>& nodes, const Bounds& bounds);
}