#pragma once

#include <utility>

#include "window.hpp"

namespace ctn {
template <typename SELF>
class AppWindowBuilder : public AbstractWindowBuilder<SELF> {
 public:
  SELF& SetMinimumSize(Vec2 minSize) {
    m_minimumSize = minSize;
    return this->self();
  }

 private:
  Vec2 m_minimumSize = Vec2(100.0f, 100.0f);

  friend class AppWindow;
};

enum class WindowBoundChangeType {
  WINDOW_CREATE,
  WINDOW_MOVE,
  WINDOW_RESIZE,
  SCREEN_RESIZE
};

struct WindowBoundChange {
  WindowBoundChangeType type;
  int side;

  static constexpr int SIDE_TOP = 1 << 0;
  static constexpr int SIDE_BOTTOM = 1 << 1;
  static constexpr int SIDE_LEFT = 1 << 2;
  static constexpr int SIDE_RIGHT = 1 << 3;
};

class AppWindow : public Window {
 protected:
  void ClampBounds(WindowBoundChange change);

 public:
  template <typename Builder,
            typename = std::enable_if_t<std::is_convertible_v<
                const Builder&, const AppWindowBuilder<Builder>&>>>
  AppWindow(WindowManager& mgr, WindowID id, const Builder& builder)
      : Window(mgr, id, builder),
        m_minimumSize(builder.m_minimumSize) {
    ClampBounds({WindowBoundChangeType::WINDOW_CREATE});
  }

 private:
  Vec2 m_minimumSize;
};

}  // namespace ctn
