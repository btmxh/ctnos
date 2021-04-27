#pragma once

#include <string>

#include "../common/rect.hpp"
#include "../graphics/nanovg.hpp"

namespace ctn {
class WindowManager;
class Window;
using WindowID = size_t;

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
  Rect2 m_bounds = {0.0f, 0.0f, 0.0f, 0.0f};
  std::string m_title = "Window";
  bool m_decorated = true;
  bool m_alwaysOnTop = false;

  friend class Window;
};
class Window {
 public:
  Window(WindowManager& mgr, WindowID id, const WindowBuilder<Window>& builder);

  virtual void Render(NvgContext& ctx, float delta);

 protected:
  WindowManager& m_mgr;
  WindowID m_id;
  Rect2 m_bounds;
  std::string m_title;
  bool m_decorated;
  bool m_alwaysOnTop;
};
}  // namespace ctn
