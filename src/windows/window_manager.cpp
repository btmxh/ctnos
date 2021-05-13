#include "window_manager.hpp"

#include <algorithm>

#include "../game.hpp"
#include "desktop_window.hpp"
#include "window.hpp"

ctn::WindowManager::WindowManager(DesktopState& state)
    : m_desktopState(state), m_input(state.GetGame().GetWindow()) {
  // clang-format off
  m_focusWindow = CreateWindow<DesktopWindow>(DesktopWindowBuilder()
    .SetDecorated(false)
    .SetAlwaysOnTop(false)
    .SetBounds({{0.0f, 0.0f}, state.GetGame().GetFramebufferSize()})
    .SetTitle("desktop_window")).m_id;
  // clang-format on
}

void ctn::WindowManager::Render(NvgContext& nvg, float delta) {
  m_input.Update();

  for (const auto id : m_windowOrder) {
    const auto& window = m_windows[id];

    window->RenderWindow(nvg, delta);
  }

  for (auto it = m_windows.begin(); it != m_windows.end();) {
    if (it->second->m_shouldClose) {
      auto id = it->first;
      it = m_windows.erase(it);
      m_windowOrder.erase(
          std::remove(m_windowOrder.begin(), m_windowOrder.end(), id),
          m_windowOrder.end());
    } else {
      ++it;
    }
  }
}

ctn::Window* ctn::WindowManager::operator[](WindowID id) {
  auto it = m_windows.find(id);

  if (it != m_windows.end()) {
    return it->second.get();
  } else {
    return nullptr;
  }
}

const ctn::Window* ctn::WindowManager::operator[](WindowID id) const {
  auto it = m_windows.find(id);

  if (it != m_windows.end()) {
    return it->second.get();
  } else {
    return nullptr;
  }
}

ctn::NvgContext& ctn::WindowManager::GetNanoVG() {
  return m_desktopState.GetNanoVG();
}

ctn::DesktopState& ctn::WindowManager::GetDesktopState() {
  return m_desktopState;
}

ctn::Input& ctn::WindowManager::GetInput() { return m_input; }

void ctn::WindowManager::Resize(Vec2 newSize) {
  for (auto& [id, window] : m_windows) {
    window->ScreenResize(newSize);
  }
}

ctn::Vec2 ctn::WindowManager::GetSize() const {
  assert(m_windows.find(DESKTOP_WINDOW) != m_windows.end());
  return m_windows.find(DESKTOP_WINDOW)->second->GetBounds().max;
}

ctn::WindowID ctn::WindowManager::GetFocusWindowID() const {
  return m_focusWindow;
}

