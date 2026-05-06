#include "weightedGraph.hpp"
#include "utils/stdUtils.hpp"

namespace DataStructure {
    void WeightedGraph::add_vertex(IDType const id) {
        adjacency_list.try_emplace(id, std::vector<WeightedArc>{});
    }

    void WeightedGraph::add_directed_edge(IDType const from, IDType const to, double const weight) {
        adjacency_list[from].push_back({to, weight});
        add_vertex(to);
    }

    void WeightedGraph::add_undirected_edge(IDType const a, IDType const b, double const weight) {
        add_directed_edge(a, b, weight);
        add_directed_edge(b, a, weight);
    }

    void WeightedGraph::remove_node(IDType const id) {
        adjacency_list.erase(id);

        // remove all edges pointing to this node
        for (auto& [_, neighbors] : adjacency_list) {
            erase_remove_if(neighbors, [&](WeightedArc const& arc) { return arc.to == id; }
            );
        }
    }

    void WeightedGraph::remove_node_undirected(IDType const id) {
        // instead of iterating over all nodes neighbors,
        // we can only iterate over the neighbors of the node 
        for (const auto& [neighbor_id, _] : get_neighbors(id)) {
            erase_remove_if(get_neighbors(neighbor_id), [&](WeightedArc const& arc) { return arc.to == id; });
        }
        
        adjacency_list.erase(id);
    }

    void WeightedGraph::remove_edge(IDType const from, IDType const to) {
        erase_remove_if(adjacency_list[from], [&](WeightedArc const& pair) { return pair.to == to; });
    }

    void WeightedGraph::remove_edge_undirected(IDType const a, IDType const b) {
        remove_edge(a, b);
        remove_edge(b, a);
    }

} // namespace
