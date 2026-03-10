#pragma once
#include "color.hpp"

namespace Color {
    RGB mix(const RGB& c1, const RGB& c2);

    float luminance(const RGB& color);

    RGB invert(const RGB& color);

    RGB grayscale(const RGB& color);
}