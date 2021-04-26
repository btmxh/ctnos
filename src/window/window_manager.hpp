#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../graphics/nanovg.hpp"

namespace ctn {
class Window;
class WindowManager {
 public:
  using WindowID = size_t;
  static constexpr WindowID DESKTOP_WINDOW = 0;
  static constexpr WindowID TASKBAR_WINDOW = 1;

  WindowManager();

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

    return itr->second;
  }

 private:
  std::unordered_map<WindowID, std::unique_ptr<Window>> m_windows;
  std::vector<WindowID> m_windowOrder;
  WindowID m_idCounter = DESKTOP_WINDOW;
};
}  // namespace ctn
