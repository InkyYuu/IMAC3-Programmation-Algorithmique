#include "simplify.hpp"

#include <iostream>
#include <random>
#include <algorithm>
#include <optional>
#include <set>
#include <vector>
#include <queue>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "utils/stdUtils.hpp"
#include "osm/positionedGraph.hpp"
#include "dataStructure/graphUtils.hpp"

void simplify_graph(PositionedGraph& graph) {
    std::cout << "Starting graph simplification. Initial graph has " << graph.nodes.size() << " nodes." << std::endl;

    keep_only_largest_connected_component(graph);
    std::cout << "Graph has " << graph.nodes.size() << " nodes after simplification [largest connected component]." << std::endl;

    remove_small_ending_edge(graph, 10.0);
    std::cout << "Graph has " << graph.nodes.size() << " nodes after simplification [small ending edges removal]." << std::endl;

    remove_degree_two_nodes_by_angle_threshold(graph, 30);
    std::cout << "Graph has " << graph.nodes.size() << " nodes after simplification [two degree nodes removal]." << std::endl;

    group_nodes_by_connection_depth_and_proximity(graph, 10.0, 6);
    std::cout << "Graph has " << graph.nodes.size() << " nodes after simplification [grouping by depth and proximity]." << std::endl;
    
    remove_degree_two_nodes_by_angle_threshold(graph, 30);
    std::cout << "Graph has " << graph.nodes.size() << " nodes after simplification [two degree nodes removal]." << std::endl;
}

void replace_node_by_arc(PositionedGraph& graph, OSM::NodeId const id) {
    // for each pair of neighbors, add new edge between them
    auto const& neighbors { graph.graph.get_neighbors(id) };
    for (size_t i {0}; i < neighbors.size(); i++) {
        for (size_t j {i + 1}; j < neighbors.size(); j++) {
            OSM::NodeId const a_id { neighbors[i].to };
            OSM::NodeId const b_id { neighbors[j].to };

            auto const& a_neighbors { graph.graph.get_neighbors(a_id) };
            auto const& b_neighbors { graph.graph.get_neighbors(b_id) };

            // if edge already exists between a and b, skip
            if(std::any_of(a_neighbors.begin(), a_neighbors.end(), [&](auto const& arc) { return arc.to == b_id; })
                || std::any_of(b_neighbors.begin(), b_neighbors.end(), [&](auto const& arc) { return arc.to == a_id; })
                // edge already exists between a and b
            ) {
                continue;
            }

            graph.add_undirected_edge(a_id, b_id);
        }
    }
    graph.remove_node(id);
}

std::optional<double> get_degree_two_node_angle(PositionedGraph const& graph, OSM::NodeId const id) {
    auto const& neighbors { graph.graph.get_neighbors(id) };
    // check degree two, return nullopt if not
    if (neighbors.size() != 2) {
        return std::nullopt;
    }

    glm::vec2 const& node_position { graph.node_position(id) };
    glm::vec2 const& node_a_position { graph.node_position(neighbors[0].to) };
    glm::vec2 const& node_b_position { graph.node_position(neighbors[1].to) };

    glm::vec<2, double> const vec_a { node_a_position - node_position };
    glm::vec<2, double> const vec_b { node_b_position - node_position };
    return glm::angle(glm::normalize(vec_a), glm::normalize(vec_b));
}

void remove_degree_two_nodes_by_angle_threshold(PositionedGraph& graph, double threshold_degrees) {
    // iterate over shuffled list of node ids to avoid order bias
    std::vector <OSM::NodeId> node_ids {};
    for (auto const& [node_id, _] : graph.nodes) {
        node_ids.push_back(node_id);
    }
    std::shuffle(node_ids.begin(), node_ids.end(), std::mt19937{std::random_device{}()});

    for (auto const& node_id : node_ids) {
        std::optional<double> const angle_optional { get_degree_two_node_angle(graph, node_id) };
        if (!angle_optional.has_value()) {
            continue;
        }

        double const angle { angle_optional.value() };
        double const diff_flat_angle { std::abs(glm::pi<double>() - angle) };

        if (diff_flat_angle < glm::radians(threshold_degrees)) {
            replace_node_by_arc(graph, node_id);
        }
    }
}

void keep_only_largest_connected_component(PositionedGraph& graph) {
    // find all connected components using DFS
    std::set<OSM::NodeId> globally_visited {};
    std::vector<std::set<OSM::NodeId>> components {};

    for (const auto& [node_id, _] : graph.nodes) {
        if (globally_visited.contains(node_id)) {
            continue;
        }

        std::set<OSM::NodeId> current_component {};
        // internal visited set will be used to build the current component 
        // but we need to keep track of global visited nodes too
        DFS(graph.graph, node_id, [&](OSM::NodeId const id) {
            globally_visited.insert(id);
            current_component.insert(id);
        });
        components.push_back(current_component);
    }

    // find largest component
    auto largest_component_it { std::max_element(
        components.begin(),
        components.end(),
        [](auto const& a, auto const& b) { return a.size() < b.size(); }
    )};

    // remove all nodes not in largest component
    std::set<OSM::NodeId> const& largest_component = *largest_component_it;
    std::vector<OSM::NodeId> nodes_to_remove {};
    for (auto const& [node_id, _] : graph.nodes) {
        if (!largest_component.contains(node_id)) {
            nodes_to_remove.push_back(node_id);
        }
    }

    for (OSM::NodeId const& node_id : nodes_to_remove) {
        graph.remove_node(node_id);
    }
}

std::vector<OSM::NodeId> get_neigbors_withing_depth(PositionedGraph const& graph, OSM::NodeId const start_node_id, size_t max_depth) {
    std::set<OSM::NodeId> visited {};
    // store depth along with node id
    std::queue<std::pair<OSM::NodeId, size_t>> to_visit {};
    to_visit.push({start_node_id, 0});

    while (!to_visit.empty()) {
        auto [current_id, current_depth] = to_visit.front();
        to_visit.pop();

        if (current_depth >= max_depth) {
            continue;
        }

        for (auto const& edge : graph.graph.get_neighbors(current_id)) {
            if (!visited.contains(edge.to)) {
                visited.insert(edge.to);
                to_visit.push({edge.to, current_depth + 1});
            }
        }
    }

    // remove start node from result
    visited.erase(start_node_id);

    return std::vector<OSM::NodeId>(visited.begin(), visited.end());
}

// Structure to store cluster information during the grouping by connection depth and proximity step
// keep it in the cpp file as it is only used in the implementation of the grouping function and does not need to be exposed in the header file
struct ClusterInfo {
    size_t cluster_size {0};
    glm::vec2 coordinates_sum {};
    std::vector<OSM::NodeId> node_ids {};

    glm::vec2 barycenter {};

    void add_node(OSM::NodeId const& node_id, glm::vec2 const& position) {
        cluster_size += 1;
        coordinates_sum += position;
        node_ids.push_back(node_id);
        update_barycenter();
    }

    void update_barycenter() {
        barycenter = coordinates_sum / static_cast<float>(cluster_size);
    }
};

void group_nodes_by_connection_depth_and_proximity(PositionedGraph& graph, double proximity_threshold_meters, size_t neighbor_depth) {
    using OSM::NodeId;
    std::vector<ClusterInfo> clusters {};

    for (const auto& [node_id, _] : graph.nodes) {
        ClusterInfo current_cluster_info {};
        glm::vec2 const& node_position { graph.node_position(node_id) };
        current_cluster_info.add_node(node_id, node_position);

        // get all neighbors within depth and check proximity
        for (NodeId const& neighbor_id : get_neigbors_withing_depth(graph, node_id, neighbor_depth)) {
            glm::vec2 const& neighbor_position { graph.node_position(neighbor_id) };
            double const distance { glm::distance(node_position, neighbor_position) };
            if(distance <= proximity_threshold_meters) {
                current_cluster_info.add_node(neighbor_id, neighbor_position);
            }
        }

        clusters.push_back(current_cluster_info);
    }

    // merge cluster that are too close to each other
    for(size_t i {0}; i < clusters.size(); ++i) {
        for(size_t j {i + 1}; j < clusters.size(); ++j) {
            ClusterInfo& cluster_a { clusters[i] };
            ClusterInfo& cluster_b { clusters[j] };

            double const distance { glm::distance(cluster_a.barycenter, cluster_b.barycenter) };
            if(distance <= proximity_threshold_meters) {
                // merge cluster_b into cluster_a
                for (const auto& node_id : cluster_b.node_ids) {
                    glm::vec2 const& node_position { graph.node_position(node_id) };
                    cluster_a.add_node(node_id, node_position);
                }
                // mark cluster_b as empty
                cluster_b.node_ids.clear();
                cluster_b.cluster_size = 0;
            }
        }
    }

    // remove empty clusters
    erase_remove_if(
        clusters,
        [](ClusterInfo const& cluster_info) { return cluster_info.cluster_size == 0; }
    );

    // at this point cluster_infos may contain overlapping nodes
    // build a map of node_id to cluster indices
    std::unordered_map<NodeId, std::vector<size_t>> nodes_clusters_indices {};
    for (size_t cluster_idx {0}; cluster_idx < clusters.size(); ++cluster_idx) {
        ClusterInfo& cluster_info { clusters[cluster_idx] };
        for (const auto& node_id : cluster_info.node_ids) {
            nodes_clusters_indices[node_id].push_back(cluster_idx);
        }
    }
    
    // if a node belongs to multiple clusters, assign it to the closest one
    std::unordered_map<NodeId, size_t> nodes_unique_cluster_index {};
    for (auto& [node_id, cluster_indices] : nodes_clusters_indices) {
        if (cluster_indices.size() <= 1) {
            continue;
        }

        glm::vec2 const& node_position { graph.node_position(node_id) };
        double min_distance { std::numeric_limits<double>::max() };
        size_t closest_cluster_idx { cluster_indices[0] };

        for (const auto& cluster_idx : cluster_indices) {
            ClusterInfo& cluster_info { clusters[cluster_idx] };
            double const distance { glm::distance(node_position, cluster_info.barycenter) };
            if (distance < min_distance) {
                min_distance = distance;
                closest_cluster_idx = cluster_idx;
            }
        }

        nodes_unique_cluster_index[node_id] =  closest_cluster_idx;
    }

    // build new groups of nodes per cluster
    std::vector<std::vector<OSM::NodeId>> nodes_groups {};
    nodes_groups.resize(clusters.size());
    for (auto const& [node_id, cluster_index] : nodes_unique_cluster_index) {
        nodes_groups[cluster_index].push_back(node_id);
    }

    // remove groups with less than 2 nodes
    erase_remove_if(
        nodes_groups,
        [](std::vector<OSM::NodeId> const& group) { return group.size() < 2; }
    );

    // merge nodes in each cluster of more than 1 node
    for (std::vector<OSM::NodeId> const& nodes_indices : nodes_groups) {
        graph.merge_nodes(nodes_indices);
    }
}

void remove_small_ending_edge(PositionedGraph& graph, double threshold_distance) {
    std::vector<OSM::NodeId> nodes_to_remove {};

    for (auto const& [node_id, node_position] : graph.nodes) {
        auto const& neighbors { graph.graph.get_neighbors(node_id) };
        // check if degree is 1
        if (neighbors.size() != 1) {
            continue;
        }

        glm::vec2 const& neighbor_position { graph.node_position(neighbors[0].to) };

        double const distance { glm::distance(node_position, neighbor_position) };
        if (distance < threshold_distance) {
            nodes_to_remove.push_back(node_id);
        }
    }

    for (OSM::NodeId const& node_id : nodes_to_remove) {
        graph.remove_node(node_id);
    }
}