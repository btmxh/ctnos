#pragma once

#include "state.hpp"

namespace ctn {
class BootState : public State {
 public:
  explicit BootState(Game& game);

  void Render(float delta);
 private:
  
};
}  // namespace ctn
