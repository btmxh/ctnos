#include "desktop_state.hpp"

#include "../game.hpp"

ctn::DesktopState::DesktopState(Game& game) : State(game), m_windows(*this)  {
  // clang-format off
  m_windows.CreateWindow<CalculatorWindow>(CalculatorWindowBuilder()
      .SetBounds({100, 100, 300, 400})
      .SetMinimumSize({100, 100}));
  // clang-format on
}

void ctn::DesktopState::Render(float delta) {
  auto& nvg = m_game.GetNanoVG();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  Vec2 framebufferSize = m_game.GetFramebufferSize();
  nvgBeginFrame(nvg, framebufferSize.x, framebufferSize.y, 1.0f);

  nvgBeginPath(nvg);

  nvgRect(nvg, 100.0f, 100.0f, 200.0f, 200.0f);
  nvgFillColor(nvg, nvgRGBf(1.0f, 0.0f, 0.0f));
  nvgFill(nvg);

  nvgClosePath(nvg);

  m_windows.Render(nvg, delta);

  nvgEndFrame(nvg);
}

ctn::NvgContext& ctn::DesktopState::GetNanoVG() { return m_game.GetNanoVG(); }

