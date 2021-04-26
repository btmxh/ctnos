#include "boot_state.hpp"

#include "../game.hpp"

ctn::BootState::BootState(Game& game) : State(game) {}

void ctn::BootState::Render(float delta) {
  auto& nvg = m_game.GetNanoVG();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  nvgBeginFrame(nvg, 1280.0f, 720.0f, 1.0f);
  nvgBeginPath(nvg);

  nvgRect(nvg, 100.0f, 100.0f, 200.0f, 200.0f);
  nvgFillColor(nvg, nvgRGBf(1.0f, 0.0f, 0.0f));
  nvgFill(nvg);

  nvgClosePath(nvg);
  nvgEndFrame(nvg);
}

