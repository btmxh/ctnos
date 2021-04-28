#include "input.hpp"

bool ctn::KeyState::pressed() const { return !lastFrame && thisFrame; }

bool ctn::KeyState::released() const { return lastFrame && !thisFrame; }

bool ctn::MouseButtonState::pressed() const {
  return !lastFrame.down && thisFrame.down;
}

bool ctn::MouseButtonState::released() const {
  return lastFrame.down && !thisFrame.down;
}

ctn::Input::Input(const vkfw::Window& window) : window(window) {
  vkfw::Key systemKeys[] = {
      vkfw::Key::eEscape, vkfw::Key::eLeftControl, vkfw::Key::eRightControl,
      // TODO: add more if needed
  };

  for (size_t i = 0; i < sizeof(systemKeys) / sizeof(systemKeys[0]); i++) {
    keys[systemKeys[i]] = {};
  }

  vkfw::MouseButton usedMouseButtons[] = {
      vkfw::MouseButton::e1, vkfw::MouseButton::e2, vkfw::MouseButton::e3,
      vkfw::MouseButton::e4, vkfw::MouseButton::e5, vkfw::MouseButton::e6,
      vkfw::MouseButton::e7, vkfw::MouseButton::e8,
  };

  for (size_t i = 0; i < sizeof(usedMouseButtons) / sizeof(usedMouseButtons[0]);
       i++) {
    mouseButtons[usedMouseButtons[i]] = {};
  }
}

ctn::KeyState& ctn::Input::operator[](Key key) { return keys[key]; }

ctn::MouseButtonState& ctn::Input::operator[](MouseButton mouseButton) {
  return mouseButtons[mouseButton];
}

void ctn::Input::Update() {
  for (auto& [key, state] : keys) {
    state.lastFrame = state.thisFrame;
    state.thisFrame = window.getKey(key);
  }

  for (auto& [mb, state] : mouseButtons) {
    state.lastFrame = state.thisFrame;
    state.thisFrame.down = window.getMouseButton(mb);
    if (state.pressed()) {
      auto [x, y] = window.getCursorPos();
      state.thisFrame.lastPressedCursorPos = {static_cast<float>(x),
                                              static_cast<float>(y)};
    }
  }
}

