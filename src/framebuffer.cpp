#include "framebuffer.h"
#include <iostream>
#include <random>

Framebuffer::Framebuffer(int width, int height)
    : width(width), height(height), clearColor(Color(0, 0, 0)), currentColor(Color(255, 255, 255))
{
    framebuffer.resize(width * height);
    clear();
}

void Framebuffer::clear()
{
    fill(framebuffer.begin(), framebuffer.end(), clearColor);
}

void Framebuffer::setClearColor(Color newColor)
{
    clearColor = newColor;
}

void Framebuffer::setCurrentColor(Color newColor)
{
    currentColor = newColor;
}

void Framebuffer::setSize(int newW, int newH)
{
    width = newW;
    height = newH;
    framebuffer.resize(width * height);
    clear();
}

void Framebuffer::point(glm::vec3 vertex)
{
    int x = static_cast<int>(vertex.x) + width / 2;
    int y = height / 2 - static_cast<int>(vertex.y);

    if (x >= 0 && x < width && y >= 0 && y < height)
        framebuffer[y * width + x] = currentColor;
}

void Framebuffer::line(glm::vec3 start, glm::vec3 end)
{
    int x0 = round(start.x), y0 = round(start.y);
    int x1 = round(end.x), y1 = round(end.y);
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        point(glm::vec3(x0,y0,0));

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void Framebuffer::triangle(glm::vec3 A, glm::vec3 B, glm::vec3 C){
    line(A,B);
    line(B,C);
    line(C,A);
}

Color *Framebuffer::getAsArray()
{
    if (framebuffer.empty())
        return nullptr;
    return &framebuffer[0];
}

int Framebuffer::getWidth()
{
    return width;
}
int Framebuffer::getHeight()
{
    return height;
}

Color Framebuffer::getClearColor()
{
    return clearColor;
}
Color Framebuffer::getCurrentColor()
{
    return currentColor;
}
