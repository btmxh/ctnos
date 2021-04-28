#pragma once

namespace ctn {
struct ButtonData {
  enum class State { NORMAL, HOVER, CLICK };

  State state;
  bool onAction;
};
}  // namespace ctn

