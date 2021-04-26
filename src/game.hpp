#pragma once

#include "graphics/nanovg.hpp"
#include "states/boot_state.hpp"
#include "states/desktop_state.hpp"
#include "vkfw/vkfw.hpp"

namespace ctn {
class Game {
 public:
  static const char MONOSPACE_FONT[], SAN_SERIF_FONT[];

  Game();

  void loop();

  NvgContext& GetNanoVG();

  BootState& GetBootState();
  DesktopState& GetDesktopState();

  void SetCurrentState(State& state);

 private:
  vkfw::UniqueInstance m_vkfw;
  vkfw::UniqueWindow m_window;

  NvgContext m_nvg;
  State* m_currentState = nullptr;

  BootState m_boot;
  DesktopState m_desktop;
};
}  // namespace ctn
