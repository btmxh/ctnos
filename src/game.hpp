#pragma once

#include "vkfw/vkfw.hpp"

#include "states/boot_state.hpp"
#include "states/desktop_state.hpp"

#include "graphics/nanovg.hpp"

namespace ctn {
class Game {
 public:
  Game();

  void loop();

  NvgContext& GetNanoVG();

 private:
  vkfw::UniqueInstance m_vkfw;
  vkfw::UniqueWindow m_window;
  
  NvgContext m_nvg;
  State* m_currentState = nullptr;

  BootState m_boot;
  DesktopState m_desktop;
};
}  // namespace ctn
