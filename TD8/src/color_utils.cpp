#include "color_utils.hpp"

Color::RGB Color::mix(const Color::RGB& c1, const Color::RGB& c2)
{
    Color::RGB mixed;
    mixed.r = (c1.r + c2.r) / 2;
    mixed.g = (c1.g + c2.g) / 2;
    mixed.b = (c1.b + c2.b) / 2;
    return mixed;
}

float Color::luminance(const Color::RGB& color)
{
    return 0.2126 * (color.r / 255.0f) + 0.7152 * (color.g / 255.0f) + 0.0722 * (color.b / 255.0f);
}

Color::RGB Color::invert(const Color::RGB& color)
{
    Color::RGB inverted;
    inverted.r = 255 - color.r;
    inverted.g = 255 - color.g;
    inverted.b = 255 - color.b;
    return inverted;
}

Color::RGB Color::grayscale(const Color::RGB& color)
{  
    Color::RGB gray;
    gray.r = gray.g = gray.b = static_cast<int>(luminance(color) * 255.0f);
    return gray;
}
