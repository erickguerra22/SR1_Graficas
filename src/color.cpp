#include "color.h"

Color::Color() : r(0), g(0), b(0)
{
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue)
{
}

uint8_t Color::getBlue()
{
    return b;
}

uint8_t Color::getRed()
{
    return r;
}

uint8_t Color::getGreen()
{
    return g;
}

std::ostream &operator<<(std::ostream &os, const Color &color)
{
    os << "\033[1;31mR:" << static_cast<int>(color.r) << "\033[0m, ";
    os << "\033[1;32mG:" << static_cast<int>(color.g) << "\033[0m, ";
    os << "\033[1;34mB:" << static_cast<int>(color.b) << "\033[0m";
    return os;
}

Color Color::operator+(const Color &color)
{
    uint8_t red = r + color.r;
    uint8_t green = g + color.g;
    uint8_t blue = b + color.b;
    return Color(red, green, blue);
}

Color Color::operator*(const float &fNumber)
{
    uint8_t red = static_cast<uint8_t>(r * fNumber);
    uint8_t green = static_cast<uint8_t>(g * fNumber);
    uint8_t blue = static_cast<uint8_t>(b * fNumber);
    return Color(red, green, blue);
}

bool Color::operator==(const Color &color)
{
    return r == color.r && b == color.b && g == color.g;
}
