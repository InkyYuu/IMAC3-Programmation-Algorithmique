#pragma once
#include "color.hpp"

namespace Color {
    RGB RGB_from_hex(unsigned int const hex);
    unsigned int RGB_to_hex_int(const RGB& color);
    RGB RGB_from_hex(const std::string& hex);
    std::string RGB_to_hex_string(const RGB& color);
}