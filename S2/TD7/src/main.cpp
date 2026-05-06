#include <cassert>
#include <filesystem>
#include <iostream>

#include "argparse/argparse.hpp"

// to be able to find data files relatively to working dir
#include "utils/pathUtils.hpp"

#include "commands/exctract.hpp"
#include "commands/saveLoad.hpp"
#include "commands/simplify.hpp"
#include "commands/draw.hpp"


int handle_extract_command(argparse::ArgumentParser& extract_command) {
    std::string const input_path { extract_command.get("input") };
    std::cout << "Input path: " << input_path << std::endl;
    std::filesystem::path const osm_file_path { pathUtils::make_absolute_path(input_path) };
    auto optional_graph { extract(osm_file_path) };

    if(!optional_graph.has_value()) {
        std::cerr << "Error extracting graph from OSM file." << std::endl;
        return 1;
    }

    auto& graph { optional_graph.value() };

    std::string const output_path { extract_command.get("output") };
    std::filesystem::path const output_file_path { pathUtils::make_absolute_path(output_path, false) };
    save_graph(graph, output_file_path);
    
    return 0;
}

int handle_simplify_command(argparse::ArgumentParser& simplify_command) {
    std::string const input_path { simplify_command.get("input") };
    std::filesystem::path const input_file_path { pathUtils::make_absolute_path(input_path) };

    auto graph { load_graph(input_file_path.string()) };

    simplify_graph(graph);

    // fallback to input path if no output specified (overwrite)
    std::string const output_path {simplify_command.present("--output").value_or(simplify_command.get("input"))};

    std::filesystem::path const output_file_path { pathUtils::make_absolute_path(output_path, false) };
    save_graph(graph, output_file_path.string());
    
    return 0;
}

int handle_visualize_command(argparse::ArgumentParser& visualize_command) {
    std::string const input_path { visualize_command.get("input") };
    std::filesystem::path const input_file_path { pathUtils::make_absolute_path(input_path) };

    auto const graph { load_graph(input_file_path.string()) };

    draw_loop(graph);
    
    return 0;
}

int handle_visualizeAndProcess_command(argparse::ArgumentParser& visualizeAndProcess_command) {
    std::string const input_path { visualizeAndProcess_command.get("input") };
    std::filesystem::path const osm_file_path { pathUtils::make_absolute_path(input_path) };
    auto optional_graph { extract(osm_file_path) };
    
    if(!optional_graph.has_value()) {
        std::cerr << "Error extracting graph from OSM file." << std::endl;
        return 1;
    }

    auto& graph { optional_graph.value() };

    std::cout << "Simplifying graph before visualization..." << std::endl;
    simplify_graph(graph);

    draw_loop(graph);
    
    return 0;
}

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("graph");

    // git add subparser
    argparse::ArgumentParser extract_command("extract");
    extract_command.add_description("read OSM file and extract graph representation");
    extract_command.add_argument("input")
    .help("Path to the OSM XML file to process")
    .required();

    extract_command.add_argument("output")
    .help("Path to the output msgpack file")
    .required();

    program.add_subparser(extract_command);

    argparse::ArgumentParser simplify_command("simplify");
    simplify_command.add_description("simplify a graph by removing unnecessary nodes and edges");
    simplify_command.add_argument("input")
    .help("Path to the input graph msgpack file")
    .required();

    simplify_command.add_argument("-o", "--output")
    .help("Path to the output simplified graph msgpack file");

    program.add_subparser(simplify_command);

    argparse::ArgumentParser visualize_command("visualize");
    visualize_command.add_description("visualize a graph from a msgpack file");
    visualize_command.add_argument("input")
    .help("Path to the input graph msgpack file")
    .required();
    program.add_subparser(visualize_command);

    argparse::ArgumentParser visualizeAndProcess_command("visualizeAndProcess");
    visualizeAndProcess_command.add_description("visualize and process a graph from osm file");
    visualizeAndProcess_command.add_argument("input")
    .help("Path to the input OSM XML file")
    .required();
    program.add_subparser(visualizeAndProcess_command);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    std::cout << "Graph processing tool\n";

    if(program.is_subcommand_used(extract_command)) {
        return handle_extract_command(extract_command);
    }
    else if(program.is_subcommand_used(simplify_command)) {
        return handle_simplify_command(simplify_command);
    }
    else if(program.is_subcommand_used(visualize_command)) {
        return handle_visualize_command(visualize_command);
    }
    else if(program.is_subcommand_used(visualizeAndProcess_command)) {
        return handle_visualizeAndProcess_command(visualizeAndProcess_command);
    }
    else {
        std::cerr << "No subcommand specified.\n";
        std::cerr << program;
        return 1;
    }
}