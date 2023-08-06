#include <SDL.h>
#include "framebuffer.h"
#include "renderbuffer.h"
#include "setupVertexArray.h"
#include "loadOBJ.h"
#include <Windows.h>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

int scale = 1;
Framebuffer framebuffer = Framebuffer(100, 100);
std::vector<glm::vec3> vertexList;
float rotationAngle = glm::radians(0.0f); // Change the angle as needed

void printVertex(glm::vec3 vertex)
{
  SDL_Log("Vértice: (%f, %f, %f)\n", vertex.x, vertex.y, vertex.z);
}

void drawModel()
{
  glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle+=0.01, glm::vec3(0.0f, 1.0f, 0.0f));

  for (int i = 2; i < vertexList.size(); i += 3)
  {
    glm::vec4 rotatedVertex1 = rotationMatrix * glm::vec4(vertexList[i-2], 1.0f);
    glm::vec4 rotatedVertex2 = rotationMatrix * glm::vec4(vertexList[i-1], 1.0f);
    glm::vec4 rotatedVertex3 = rotationMatrix * glm::vec4(vertexList[i], 1.0f);
    framebuffer.triangle(glm::vec3(rotatedVertex1), glm::vec3(rotatedVertex2), glm::vec3(rotatedVertex3));
  }
}

void render(SDL_Renderer *renderer)
{
  framebuffer.clear();
  drawModel();
  renderBuffer(renderer, framebuffer);
}

int main(int argv, char **args)
{
  framebuffer.setSize(GetSystemMetrics(SM_CXSCREEN) / scale, (GetSystemMetrics(SM_CYSCREEN) - 25) / scale);

  std::vector<glm::vec3> out_vertices;
  std::vector<Face> out_faces;

  loadOBJ("D:/Documentos/UVG/6to Semestre/Graficas/Laboratorios/lab3/part_1/Lab3_1.obj", out_vertices, out_faces);

  vertexList = setupVertexArray(out_vertices, out_faces);

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window = SDL_CreateWindow("SR1: Carga de modelo", 0, 25, framebuffer.getWidth() * scale, framebuffer.getHeight() * scale, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_RenderSetScale(renderer, scale, scale);

  SDL_Event event;

  bool isRunning = true;
  while (isRunning)
  {
    while (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT)
      {
        isRunning = false;
      }
    }

    render(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(1);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}