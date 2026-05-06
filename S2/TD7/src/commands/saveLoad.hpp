#pragma once

#include <filesystem>

#include "osm/positionedGraph.hpp"

void save_graph(PositionedGraph& graph, std::filesystem::path const& path);
PositionedGraph load_graph(std::filesystem::path const& path);

// void test_pack_unpack(PositionedGraph& graph);