#pragma once

#include "weightedGraph.hpp"

#include <unordered_map>
#include <vector>

void DFS(DataStructure::WeightedGraph const& graph, DataStructure::IDType const start, std::function<void(DataStructure::IDType const)> const& callback, std::function<bool(DataStructure::IDType const)> const& should_explore_neighbors = [](DataStructure::IDType const) { return true; });

void print_DFS(DataStructure::WeightedGraph const& graph, DataStructure::IDType const start);

// Dijkstra's algorithm implementation
// return a map of node id to pair of weight and parent node id (for path reconstruction)
std::unordered_map<DataStructure::IDType, std::pair<float, DataStructure::IDType>> Dijkstra(DataStructure::WeightedGraph const& graph, DataStructure::IDType const start, DataStructure::IDType const end);

// reconstruct the path from the distances map returned by Dijkstra's algorithm
std::vector<DataStructure::IDType> reconstruct_path(std::unordered_map<DataStructure::IDType, std::pair<float, DataStructure::IDType>> const& distances, DataStructure::IDType const start, DataStructure::IDType const end);

// helper function to directly get the path from Dijkstra's algorithm
std::vector<DataStructure::IDType> dijkstra_path(DataStructure::WeightedGraph const& graph, DataStructure::IDType const start, DataStructure::IDType const end);