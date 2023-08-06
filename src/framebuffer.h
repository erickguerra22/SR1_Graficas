#pragma once
#include <vector>
#include "color.h"
#include <glm/glm.hpp>

class Framebuffer
{
private:
    int width;
    int height;
    std::vector<Color> framebuffer;
    Color clearColor;
    Color currentColor;

public:
    Framebuffer(int width, int height);

    void clear();
    void setClearColor(Color newColor);
    void setCurrentColor(Color newColor);
    void setSize(int newW, int newH);

    void point(glm::vec3 vertex);
    void line(glm::vec3 start, glm::vec3 end);
    void triangle(glm::vec3 A, glm::vec3 B, glm::vec3 C);
    Color *getAsArray();

    int getWidth();
    int getHeight();
    Color getClearColor();
    Color getCurrentColor();
};
