#pragma once

#include "glm/glm.hpp"
#include "graphics/nanovg.hpp"
#include "states/boot_state.hpp"
#include "states/desktop_state.hpp"

#define VKFW_NO_INCLUDE_VULKAN_HPP
#include "vkfw/vkfw.hpp"

namespace ctn {
class Game {
 public:
  static const char MONOSPACE_FONT[], SAN_SERIF_FONT[];

  Game();

  void loop();

  NvgContext& GetNanoVG();
  vkfw::Window& GetWindow();

  BootState& GetBootState();
  DesktopState& GetDesktopState();

  void SetCurrentState(State& state);

  template <typename T = float, glm::qualifier glmQ = glm::defaultp>
  glm::vec<2, T, glmQ> GetFramebufferSize() const {
    auto [w, h] = m_window->getFramebufferSize();
    return {static_cast<T>(w), static_cast<T>(h)};
  }

 private:
  vkfw::UniqueInstance m_vkfw;
  vkfw::UniqueWindow m_window;

  NvgContext m_nvg;
  State* m_currentState = nullptr;

  BootState m_boot;
  DesktopState m_desktop;
};
}  // namespace ctn
