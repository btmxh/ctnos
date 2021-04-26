#include "game.hpp"

#include <chrono>

#include "glad/gl.h"

ctn::Game::Game()
    : m_vkfw(vkfw::initUnique()),
      m_window([&]() {
        vkfw::WindowHints hints;
        hints.clientAPI = vkfw::ClientAPI::eOpenGL;
        auto window = vkfw::createWindow(1280, 720, "ctnos", hints);
        window.makeContextCurrent();
        if (!gladLoadGL(glfwGetProcAddress)) {
          throw std::runtime_error("Error loading OpenGL functions");
        }

        return window;
      }()),
      m_boot(*this),
      m_desktop(*this),
      m_currentState(&m_boot) {}

void ctn::Game::loop() {
  auto lastFrame = std::chrono::high_resolution_clock::now();

  while (!m_window->shouldClose()) {
    vkfw::pollEvents();

    auto now = std::chrono::high_resolution_clock::now();

    auto delta =
        std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastFrame)
            .count() /
        1e9f;

    if (m_currentState) {
      m_currentState->Render(delta);
    }

    m_window->swapBuffers();
  }
}

ctn::NvgContext& ctn::Game::GetNanoVG() {
  return m_nvg;
}

