#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <functional>

#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"

namespace DataStructure {
    using IDType = uint64_t;
    
    struct WeightedArc {
        IDType to {};
        double weight {1.0f};

        bool operator==(WeightedArc const& other) const = default;
        bool operator!=(WeightedArc const& other) const = default;

        template<class Archive>
        void serialize(Archive & archive) {
            archive(
                cereal::make_nvp("to",to),
                cereal::make_nvp("weight",weight)
            );
        }
    };
    
    struct WeightedGraph {
    
        std::unordered_map<IDType, std::vector<WeightedArc>> adjacency_list {};

        void add_vertex(IDType const id);

        void add_directed_edge(IDType const from, IDType const to, double const weight = 1.0f);
        void add_undirected_edge(IDType const a, IDType const b, double const weight = 1.0f);

        void remove_node(IDType const id);
        // optim in case we know the graph is undirected
        void remove_node_undirected(IDType const id);

        void remove_edge(IDType const from, IDType const to);
        void remove_edge_undirected(IDType const a, IDType const b);

        inline std::vector<WeightedArc>& get_neighbors(IDType const id) { return adjacency_list.at(id); }
        inline std::vector<WeightedArc> const& get_neighbors(IDType const id) const { return adjacency_list.at(id); }

        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        template<class Archive>
        void serialize(Archive & archive) {
            archive(cereal::make_nvp("adjacency_list", adjacency_list));
        }
    };
} // namespace DataStructure