#pragma once

#include <unordered_map>

#include "../common/rect.hpp"
#include "vkfw/vkfw.hpp"

namespace ctn {
using Key = vkfw::Key;
using MouseButton = vkfw::MouseButton;

template <typename T>
struct InputState {
  T lastFrame{};
  T thisFrame{};

  T* operator->() { return &thisFrame; }
  const T* operator->() const { return &thisFrame; }
};

struct MouseButtonInfo {
  bool down = false;
  Vec2 lastPressedCursorPos = {NAN, NAN};
};

struct KeyState : public InputState<bool> {
  bool pressed() const;
  bool released() const;
};

struct MouseButtonState : public InputState<MouseButtonInfo> {
  bool pressed() const;
  bool released() const;
};

struct CursorPosState : public InputState<Vec2> {
  bool In(const Rect2& rect) const;
  bool Entered(const Rect2& rect) const;
  bool Exited(const Rect2& rect) const;
};

struct Input {
  explicit Input(const vkfw::Window& window);

  const vkfw::Window& window;
  std::unordered_map<Key, KeyState> keys;
  std::unordered_map<MouseButton, MouseButtonState> mouseButtons;
  CursorPosState cursor;

  KeyState& operator[](Key key);
  MouseButtonState& operator[](MouseButton mouseButton);

  void Update();
};
}  // namespace ctn

