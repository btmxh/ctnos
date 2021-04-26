#include "window_manager.hpp"
#include "window.hpp"

ctn::WindowManager::WindowManager() {}

void ctn::WindowManager::Render(NvgContext &nvg, float delta) {
  for(const auto id : m_windowOrder) {
    const auto& window = m_windows[id];

    window->Render(nvg, delta);
  }
}

