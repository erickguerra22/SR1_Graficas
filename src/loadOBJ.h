#include <SDL.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "face.h"

bool loadOBJ(const std::string &path, std::vector<glm::vec3> &out_vertices, std::vector<Face> &out_faces, int zoom = 60)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        SDL_Log("No se pudo abrir el archivo");
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        const char *characters = line.c_str();
        if (characters[0] == 'v' && characters[1] == ' ')
        {
            std::istringstream coordinates(line.substr(2));
            float x, y, z;

            coordinates >> x >> y >> z;

            out_vertices.push_back(glm::vec3(x * zoom, y * zoom, z * zoom));
        }
        if (characters[0] == 'f')
        {
            Face face;
            std::istringstream values(line.substr(2));
            std::string value;
            while (values >> value)
            {
                std::istringstream verts(value.substr());
                int x, y, z;
                char delimiter;
                verts >> x >> delimiter >> y >> delimiter >> z;
                face.vertexIndices.push_back({x - 1, y, z});
                out_faces.push_back(face);
            }
        }
    }
    return true;
}