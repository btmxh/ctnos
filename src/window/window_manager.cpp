#include "window_manager.hpp"

#include "../game.hpp"
#include "desktop_window.hpp"
#include "window.hpp"

ctn::WindowManager::WindowManager(DesktopState& state) : m_desktopState(state) {
  WindowBuilder<DesktopWindow> desktopWindowBuilder;

  // clang-format off
  desktopWindowBuilder
    .SetDecorated(false)
    .SetAlwaysOnTop(false)
    .SetBounds({{0.0f, 0.0f}, state.GetGame().GetFramebufferSize()})
    .SetTitle("desktop_window");
  // clang-format on

  CreateWindow<DesktopWindow>(desktopWindowBuilder);
}

void ctn::WindowManager::Render(NvgContext& nvg, float delta) {
  for (const auto id : m_windowOrder) {
    const auto& window = m_windows[id];

    window->Render(nvg, delta);
  }
}

ctn::NvgContext& ctn::WindowManager::GetNanoVG() {
  return m_desktopState.GetNanoVG();
}

ctn::DesktopState& ctn::WindowManager::GetDesktopState() {
  return m_desktopState;
}

