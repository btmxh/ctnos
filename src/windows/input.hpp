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
  template <typename ShapeClass,
            typename = std::enable_if_t<
                std::is_convertible_v<ShapeClass&, Shape<ShapeClass>&>>>
  bool In(const ShapeClass& shape) const {
    return shape.ContainsPoint(thisFrame);
  }

  template <typename ShapeClass,
            typename = std::enable_if_t<
                std::is_convertible_v<ShapeClass, Shape<ShapeClass>>>>
  bool Enter(const ShapeClass& shape) const {
    return shape.ContainsPoint(thisFrame) && !shape.ContainsPoint(lastFrame);
  }

  template <typename ShapeClass,
            typename = std::enable_if_t<
                std::is_convertible_v<ShapeClass, Shape<ShapeClass>>>>
  bool Exit(const ShapeClass& shape) const {
    return !shape.ContainsPoint(thisFrame) && shape.ContainsPoint(lastFrame);
  }
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

