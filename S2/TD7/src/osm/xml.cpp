#include "xml.hpp"

namespace OSM {
    NodeId IDFromAttribute(const pugi::xml_attribute& attr) {
        return attr.as_llong();
    }

    std::vector<Node> extract_nodes_from_osm(const pugi::xml_document& doc) {
        std::vector<Node> nodes {};
        for (const auto& node : doc.child("osm").children("node")) {
            nodes.push_back(
                Node{
                .id= IDFromAttribute(node.attribute("id")),
                .coordinates = { node.attribute("lat").as_float(), node.attribute("lon").as_float()}
            });
        }
        return nodes;
    }

    std::vector<Way> extract_ways_from_osm(const pugi::xml_document& doc) {
        std::vector<Way> ways {};
        for (auto const& way : doc.child("osm").children("way")) {
            Way osm_way {};
            osm_way.id = IDFromAttribute(way.attribute("id"));
            for (auto const& nd : way.children("nd")) {
                osm_way.node_ids.emplace_back(IDFromAttribute(nd.attribute("ref")));
            }

            for (auto const& tag : way.children("tag")) {
                osm_way.tags.emplace_back(
                    std::string(tag.attribute("k").value()),
                    std::string(tag.attribute("v").value())
                );
            }

            ways.emplace_back(std::move(osm_way));
        }
        return ways;
    }

    Bounds extract_bounds_from_osm(const pugi::xml_document& doc) {
        auto const& bounds_node { doc.child("osm").child("bounds") };
        return {
            .min= {bounds_node.attribute("minlat").as_float(), bounds_node.attribute("minlon").as_float()},
            .max= {bounds_node.attribute("maxlat").as_float(), bounds_node.attribute("maxlon").as_float()}
        };
    }

} // namespace OSMUtils