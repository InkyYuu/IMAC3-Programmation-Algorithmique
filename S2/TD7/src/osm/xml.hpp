#pragma once

#include <vector>

#include "data.hpp"
#include "pugixml.hpp"

namespace OSM {
    NodeId IDFromAttribute(const pugi::xml_attribute& attr);
    Bounds extract_bounds_from_osm(const pugi::xml_document& doc);
    std::vector<Node> extract_nodes_from_osm(const pugi::xml_document& doc);
    std::vector<Way> extract_ways_from_osm(const pugi::xml_document& doc);
}