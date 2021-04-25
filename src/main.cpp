#include <iostream>

#define VKFW_NO_INCLUDE_VULKAN_HPP
#include "vkfw.hpp"
#include "glad/gl.h"

int main() {
  auto vkfw = vkfw::initUnique();

  vkfw::WindowHints hints;
  hints.clientAPI = vkfw::ClientAPI::eOpenGL;
  auto window = vkfw::createWindowUnique(1280, 720, "ctnos", hints);

  window->makeContextCurrent();

  gladLoadGL(glfwGetProcAddress);

  while (!window->shouldClose()) {
    vkfw::pollEvents();

    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    window->swapBuffers();
  }

  return 0;
}
