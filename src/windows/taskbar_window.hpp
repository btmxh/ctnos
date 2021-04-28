#pragma once

#include "window_manager.hpp"

namespace ctn {
class TaskbarWindowBuilder
    : public AbstractWindowBuilder<TaskbarWindowBuilder> {};

class TaskbarWindow : public Window {
 public:
  TaskbarWindow(WindowManager& mgr, WindowID id,
                const TaskbarWindowBuilder& builder);

  void RenderContent(float delta);
};
}  // namespace ctn

