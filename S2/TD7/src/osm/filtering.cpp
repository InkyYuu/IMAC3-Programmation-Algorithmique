#include "filtering.hpp"

#include <vector>
#include <algorithm>
#include <unordered_map>

#include "utils/stdUtils.hpp"

namespace OSM {
    void remove_building_ways(std::vector<Way>& ways) {
        erase_remove_if(ways,
            [](Way const& way) {
                return std::any_of(way.tags.begin(), way.tags.end(),
                [](auto const& tag) { return tag.first == "building"; });
        });
    }

    void remove_railway_ways(std::vector<Way>& ways) {
        erase_remove_if(ways,
            [](Way const& way) {
                return std::any_of(way.tags.begin(), way.tags.end(),
                [](auto const& tag) { return tag.first == "railway" || tag.second == "railway"; });
        });
    }

    void keep_way_in_bounds(std::vector<Way>& ways, std::vector<Node>& nodes, const Bounds& bounds) {
        std::unordered_map<NodeId, const Node*> node_map {};
        for (auto const& node : nodes) {
            node_map[node.id] = &node;
        }

        auto get_node_by_id = [&node_map](NodeId const& id) -> Node const& {
            return *node_map.at(id);
        };
        erase_remove_if(ways,
            [&](Way const& way) {
                return std::any_of(way.node_ids.begin(), way.node_ids.end(),
                [&](NodeId const& node_id) {
                    Node const& node { get_node_by_id(node_id) };
                    return !bounds.contains(node.coordinates);
                });
        });
    }
} // namespace OSM