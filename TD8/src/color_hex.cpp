#include "color_hex.hpp"

Color::RGB Color::RGB_from_hex(unsigned int const hex)
{
    Color::RGB color;
    color.r = (hex >> 16) & 0xFF; // Possible de faire 0xFF0000 & (hex >> 16)
    color.g = (hex >> 8) & 0xFF; // Possible de faire 0x00FF00 & (hex >> 8)
    color.b = hex & 0xFF; // Possible de faire 0x0000FF & hex
    return color;
}

unsigned int Color::RGB_to_hex_int(const Color::RGB& color)
{
    return (color.r << 16) | (color.g << 8) | color.b;
}

Color::RGB Color::RGB_from_hex(const std::string& hex)
{
    unsigned int value;
    if (hex[0] == '0' && hex[1] == 'x')
    {
        /*  -- EXPLICATION --
            stoul permet de convertir une string en unsigned int avec la base en 3eme argument
            doc stoul : https://cplusplus.com/reference/string/stoul/ ou https://en.cppreference.com/w/cpp/string/basic_string/stoul
            substr(2) permet de retirer les 2 premiers caracteres de la string (ici "0x")
            16 est la base hexadecimale
        */
        value = std::stoul(hex.substr(2), nullptr, 16);
    } else if (hex[0] == '#') {
        value = std::stoul(hex.substr(1), nullptr, 16);
    } else {
        value = std::stoul(hex, nullptr, 16);
    }
    return RGB_from_hex(value);
}

std::string Color::RGB_to_hex_string(const Color::RGB& color)
{
    std::string hex = "0x";
    hex += (color.r < 16 ? "0" : "") + std::to_string(color.r);
    hex += (color.g < 16 ? "0" : "") + std::to_string(color.g);
    hex += (color.b < 16 ? "0" : "") + std::to_string(color.b);
    return hex;
}