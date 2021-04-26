#include "game.hpp"

#include <chrono>

#include "glad/gl.h"

const char ctn::Game::MONOSPACE_FONT[] = "monospace_font";
const char ctn::Game::SAN_SERIF_FONT[] = "san_serif_font";

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
      m_nvg(),
      m_boot(*this),
      m_desktop(*this),
      m_currentState(&m_boot) {
  nvgCreateFont(m_nvg, MONOSPACE_FONT,
                "fonts/liberation/LiberationMono-Regular.ttf");
  nvgCreateFont(m_nvg, SAN_SERIF_FONT,
                "fonts/liberation/LiberationSans-Regular.ttf");
}

void ctn::Game::loop() {
  auto lastFrame = std::chrono::high_resolution_clock::now();

  while (!m_window->shouldClose()) {
    vkfw::pollEvents();

    auto now = std::chrono::high_resolution_clock::now();

    auto delta =
        std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastFrame)
            .count() /
        1e9f;
    lastFrame = now;

    if (m_currentState) {
      m_currentState->Render(delta);
    }

    m_window->swapBuffers();
  }
}

ctn::NvgContext& ctn::Game::GetNanoVG() { return m_nvg; }

ctn::BootState& ctn::Game::GetBootState() {
  return m_boot;
}

ctn::DesktopState& ctn::Game::GetDesktopState() {
  return m_desktop;
}

void ctn::Game::SetCurrentState(State &state) {
  m_currentState = &state;
}

