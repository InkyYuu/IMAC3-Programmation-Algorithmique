#include <filesystem>
#include <optional>

#include "osm/positionedGraph.hpp"

std::optional<PositionedGraph> extract(std::filesystem::path const& osm_file_path);