#pragma once

#include "dataStructure/weightedGraph.hpp"

#include "osm/data.hpp"

#include "glm/vec2.hpp"
#include <unordered_map>

#include "utils/cerealglm.hpp"
#include "cereal/types/unordered_map.hpp"

struct PositionedGraph {
    // store nodes positions for each node id (as WeightedGraph only stores ids and edges weights not node positions)
    std::unordered_map<OSM::NodeId, glm::vec2> nodes {};

    // internal generic graph representation
    DataStructure::WeightedGraph graph {};

    glm::vec2& node_position(OSM::NodeId const id) {
        return nodes.at(id);
    }
    glm::vec2 const& node_position(OSM::NodeId const id) const {
        return nodes.at(id);
    }

    void add_node(OSM::NodeId const id, glm::vec2 const& position);
    void add_undirected_edge(OSM::NodeId const from, OSM::NodeId const to);
    void remove_node(OSM::NodeId const id);
    void remove_edge(OSM::NodeId const from, OSM::NodeId const to);

    void merge_nodes(OSM::NodeId const a, OSM::NodeId const b);
    void merge_nodes(std::vector<OSM::NodeId> const& node_ids);

    std::vector<std::tuple<OSM::NodeId, OSM::NodeId, double>> get_edges_list() const;

    bool operator==(PositionedGraph const& other) const = default;
    bool operator!=(PositionedGraph const& other) const = default;

    template<class Archive>
    void serialize(Archive & archive) {
        archive(
            cereal::make_nvp("nodes", nodes),
            cereal::make_nvp("graph",graph)
        );
    }
};