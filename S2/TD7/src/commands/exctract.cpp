#include "exctract.hpp"

#include <iostream>
#include <optional>
#include <vector>
#include <unordered_map>

#include "glm/ext/vector_float2.hpp"

#include <osm/data.hpp>
#include <osm/xml.hpp>
// https://github.com/chrberger/WGS84toCartesian/
#include "osm/WGS84toCartesian.hpp"
#include "osm/filtering.hpp"
#include "osm/positionedGraph.hpp"

// https://wiki.openstreetmap.org/wiki/Paris (lat, lon)
constexpr glm::vec2 paris_coordinates {48.8533249f, 2.3488596f};

glm::vec2 toCartesian(glm::vec2 const& coordinates, glm::vec2 const& reference) {
    std::array<double, 2> const result {wgs84::toCartesian({reference.x, reference.y}, {coordinates.x, coordinates.y})};
    // flip y to draw graph with positive y up (as in math) instead of positive y down (as in screen coordinates)
    // TODO: find a better solution for this, to do that only in drawing phase
    return glm::vec2 { result[0], -result[1] };
}

PositionedGraph build_graph_from_osm(std::vector<OSM::Node> const& nodes, std::vector<OSM::Way> const& ways, OSM::Bounds const& bounds, bool filter_out_of_bounds = true) {
    PositionedGraph graph {};

    std::unordered_map<OSM::NodeId, OSM::Node const*> node_map {};
    for (OSM::Node const& node : nodes) {
        node_map[node.id] = &node;
    }

    glm::vec2 const bound_min {toCartesian(bounds.min, paris_coordinates)};
    glm::vec2 const bound_max {toCartesian(bounds.max, paris_coordinates)};
    glm::vec2 const bounds_center { (bound_min + bound_max) / 2.0f };

    for (OSM::Way const& way : ways) {
        // only add nodes that are part of ways
        for (OSM::NodeId const& node_id : way.node_ids) {
            // filter nodes not in node list
            if (!node_map.contains(node_id)) {
                std::cerr << "Warning: Node ID " << node_id << " in way " << way.id << " not found in nodes list." << std::endl;
                continue;
            }
            OSM::Node const& node { *node_map[node_id] };

            // filter nodes outside bounds
            if (filter_out_of_bounds && !bounds.contains(node.coordinates)) {
                continue;
            }

            // center the graph around the bounds center
            glm::vec2 position {toCartesian(node.coordinates, paris_coordinates)};

            position -= bounds_center;

            graph.add_node(node.id, position);
        }

        // add edges between consecutive nodes in the way
        for (size_t i {1}; i < way.node_ids.size(); i++) {
            OSM::NodeId const& from_id { way.node_ids[i - 1] };
            OSM::NodeId const& to_id { way.node_ids[i] };

            // only add edge if both nodes exist in the graph
            if (!graph.nodes.contains(from_id) || !graph.nodes.contains(to_id)) {
                continue;
            }

            graph.add_undirected_edge(from_id, to_id);
        }
    }

    return graph;
}

std::optional<PositionedGraph> extract(std::filesystem::path const& osm_file_path) {

    pugi::xml_document doc {};
    pugi::xml_parse_result result { doc.load_file(osm_file_path.c_str()) };
    if (!result) {
        std::cerr << "Error loading OSM file: " << result.description() << std::endl;
        return std::nullopt;
    }

    // Extract nodes, ways, and bounds from OSM XML
    std::vector<OSM::Node> nodes {OSM::extract_nodes_from_osm(doc)};
    OSM::Bounds bounds { OSM::extract_bounds_from_osm(doc) };
    std::vector<OSM::Way> ways { OSM::extract_ways_from_osm(doc) };
    
    // print some infos
    std::cout << nodes.size() << " nodes Loaded from OSM file." << std::endl;
    std::cout << ways.size() << " ways Loaded from OSM file." << std::endl;

    // filtering and build graph
    OSM::remove_building_ways(ways);
    OSM::remove_railway_ways(ways);
    PositionedGraph graph { build_graph_from_osm(nodes, ways, bounds, true) };

    return std::make_optional(graph);
}