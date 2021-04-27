#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../graphics/nanovg.hpp"
#include "window.hpp"

namespace ctn {
class DesktopState;

class WindowManager {
 public:
  static constexpr WindowID DESKTOP_WINDOW = 0;
  static constexpr WindowID TASKBAR_WINDOW = 1;

  explicit WindowManager(DesktopState& state);

  WindowManager(const WindowManager&) = delete;
  WindowManager(WindowManager&&) = delete;

  void Render(NvgContext& nvg, float delta);

  template <class WindowClass, typename... Args>
  WindowClass& CreateWindow(Args&&... args) {
    size_t id = m_idCounter++;
    auto window =
        std::make_unique<WindowClass>(*this, id, std::forward<Args>(args)...);
    auto [itr, inserted] =
        m_windows.insert(std::make_pair(id, std::move(window)));
    m_windowOrder.push_back(id);
    assert(inserted);

    return static_cast<WindowClass&>(*itr->second);
  }

  NvgContext& GetNanoVG();

  DesktopState& GetDesktopState();

 private:
  DesktopState& m_desktopState;
  std::unordered_map<WindowID, std::unique_ptr<Window>> m_windows;
  std::vector<WindowID> m_windowOrder;
  WindowID m_idCounter = DESKTOP_WINDOW;
};
}  // namespace ctn
