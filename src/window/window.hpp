#pragma once

#include "../common/rect.hpp"
#include "window_manager.hpp"

namespace ctn {
class Window;

template <typename WindowClass>
class WindowBuilder {
 private:
  using BuilderType = WindowBuilder<WindowClass>;

 public:
  WindowBuilder() {}

  BuilderType& SetBounds(const Rect2& bounds) {
    m_bounds = bounds;
    return *this;
  }

  BuilderType& SetTitle(const std::string& title) {
    m_title = title;
    return *this;
  }

  BuilderType& SetDecorated(bool decorated) {
    m_decorated = decorated;
    return *this;
  }

  BuilderType& SetAlwaysOnTop(bool alwaysOnTop) {
    m_alwaysOnTop = alwaysOnTop;
    return *this;
  }

 private:
  Rect2 m_bounds;
  std::string m_title;
  bool m_decorated;
  bool m_alwaysOnTop;

  friend class Window;
};
class Window {
 public:
  Window(WindowManager& mgr, WindowManager::WindowID id,
         const WindowBuilder<Window>& builder);

  virtual void Render(NvgContext& ctx, float delta);

 private:
  WindowManager& m_mgr;
  WindowManager::WindowID m_id;
  Rect2 m_bounds;
  std::string m_title;
  bool m_decorated;
  bool m_alwaysOnTop;
};
}  // namespace ctn
