#pragma once

#include "window_manager.hpp"

namespace ctn {
class TaskbarWindow;
template <>
class WindowBuilder<TaskbarWindow> : public WindowBuilder<Window> {};

class TaskbarWindow : public Window {
 public:
  TaskbarWindow(WindowManager& mgr, WindowID id,
                const WindowBuilder<TaskbarWindow>& builder);

  void Render(float delta);
};
}  // namespace ctn

