#include "saveLoad.hpp"

#include <fstream>
#include <sstream>
// #include <iostream>

#include "osm/positionedGraph.hpp"

#include <cereal/archives/xml.hpp>
#include <cereal/archives/binary.hpp>

void save_graph(PositionedGraph& graph, std::filesystem::path const& path) {
    std::ofstream output_file(path, std::stringstream::binary);
    {
        cereal::BinaryOutputArchive oarchive(output_file);
        oarchive(graph);
    }
    output_file.close();
}

PositionedGraph load_graph(std::filesystem::path const& path) {
    std::ifstream input_file(path, std::stringstream::binary);
    PositionedGraph graph;
    {
        cereal::BinaryInputArchive iarchive(input_file);
        iarchive(graph);
    }
    input_file.close();
    return graph;
}

// void test_pack_unpack(PositionedGraph& graph) {
//     std::stringstream ss;
//     {
//         cereal::BinaryOutputArchive oarchive(ss);
//         oarchive(graph);
//     }

//     PositionedGraph graph_unpack;
//     {
//         cereal::BinaryInputArchive iarchive(ss);
//         iarchive(graph_unpack);
//     }

//     if (graph_unpack != graph) {
//         std::cerr << "Error: Unpacked graph does not match original graph!" << std::endl;
//     }
// }