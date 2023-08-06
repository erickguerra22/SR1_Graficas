#include <SDL.h>
#include "framebuffer.h"
#include "renderbuffer.h"
#include "setupVertexArray.h"
#include "loadOBJ.h"
#include <Windows.h>
#include <glm/glm.hpp>
#include <iostream>

int scale = 1;
Framebuffer framebuffer = Framebuffer(100, 100);
std::vector<glm::vec3> vertexList;

void printVertex(glm::vec3 vertex)
{
  SDL_Log("Vértice: (%f, %f, %f)\n", vertex.x, vertex.y, vertex.z);
}

void drawModel()
{
  for (int i = 2; i < vertexList.size(); i += 3)
  {
    framebuffer.triangle(vertexList[i - 2], vertexList[i - 1], vertexList[i]);
  }
}

void render(SDL_Renderer *renderer)
{
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
    SDL_Delay(100);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}