#pragma once

#include "osm/positionedGraph.hpp"
#include <optional>
#include <vector>

void simplify_graph(PositionedGraph& graph);

// remove a given node and connect its neighbors together
void replace_node_by_arc(PositionedGraph& graph, OSM::NodeId const id);

// return the angle between the two neighbors of a degree two node, return nullopt if the node is not degree two
std::optional<double> get_degree_two_node_angle(PositionedGraph const& graph, OSM::NodeId const id);
// remove all nodes with degree two by connecting their neighbors together
void remove_degree_two_nodes_by_angle_threshold(PositionedGraph& graph, double threshold_degrees);

// keep only the largest connected component of the graph and remove all other nodes
void keep_only_largest_connected_component(PositionedGraph& graph);

// return the neighbors of a node within a certain depth
std::vector<OSM::NodeId> get_neigbors_withing_depth(PositionedGraph const& graph, OSM::NodeId const start_node_id, size_t max_depth);

// group nodes that are close to each other and have similar neighbors within a certain depth, then merge them together
void group_nodes_by_connection_depth_and_proximity(PositionedGraph& graph, double proximity_threshold_meters, size_t neighbor_depth = 1);

// remove nodes with degree 1 that are close to their only neighbor
void remove_small_ending_edge(PositionedGraph& graph, double threshold_distance);