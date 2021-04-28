#pragma once

#include "../windows/window_manager.hpp"
#include "state.hpp"

namespace ctn {
class DesktopState : public State {
 public:
  DesktopState(Game& game);

  void Render(float delta);

  NvgContext& GetNanoVG();

 private:
  WindowManager m_windows;
};
}  // namespace ctn
