#include "positionedGraph.hpp"

#include "osm/data.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <set>

void PositionedGraph::add_node(OSM::NodeId const id, glm::vec2 const& position) {
    nodes.try_emplace(id, position);
    graph.add_vertex(id);
}

void PositionedGraph::add_undirected_edge(OSM::NodeId const from, OSM::NodeId const to) {
    graph.add_undirected_edge(from, to, glm::distance(node_position(from), node_position(to)));
}

void PositionedGraph::remove_node(OSM::NodeId const id) {
    nodes.erase(id);
    graph.remove_node_undirected(id);
}

void PositionedGraph::remove_edge(OSM::NodeId const from, OSM::NodeId const to) {
    graph.remove_edge_undirected(from, to);
}

void PositionedGraph::merge_nodes(OSM::NodeId const a, OSM::NodeId const b) {
    merge_nodes({a, b});
}

void PositionedGraph::merge_nodes(std::vector<OSM::NodeId> const& node_ids) {
    if (node_ids.size() < 2) {
        return;
    }

    // maybe expose multiple id policy: keep first id as base for merged node id
    OSM::NodeId const merged_id { node_ids[0] };
    glm::vec2 coordinates_barycenter {0.f, 0.f};
    for (const auto& node_id : node_ids) {
        coordinates_barycenter += node_position(node_id);
    }
    coordinates_barycenter /= static_cast<float>(node_ids.size());

    std::set<OSM::NodeId> neighbor_ids {};
    for (const OSM::NodeId& node_id : node_ids) {
        for (auto const& [neighbor_id, _] : graph.get_neighbors(node_id)) {
            neighbor_ids.insert(neighbor_id);
        }
    }

    //remove original nodes from neighbor list
    for (const OSM::NodeId& node_id : node_ids) {
        neighbor_ids.erase(node_id);
    }

    // remove original nodes
    for (const OSM::NodeId& node_id : node_ids) {
        remove_node(node_id);
    }

    add_node(merged_id, coordinates_barycenter);

    // connect merged node to all neighbors
    for (const OSM::NodeId& neighbor_id : neighbor_ids) {
        add_undirected_edge(merged_id, neighbor_id);
    }
}

std::vector<std::tuple<OSM::NodeId, OSM::NodeId, double>> PositionedGraph::get_edges_list() const {
    std::vector<std::tuple<OSM::NodeId, OSM::NodeId, double>> edges {};

    for (const auto& [from, neighbors] : graph.adjacency_list) {
        for (const auto& arc : neighbors) {
            // To avoid duplicates only add edge if from < to
            if (from < arc.to) {
                edges.emplace_back(from, arc.to, arc.weight);
            }
        }
    }

    return edges;
}
