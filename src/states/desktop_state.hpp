#pragma once

#include "state.hpp"

namespace ctn {
  class DesktopState : public State {
    public:
      DesktopState(Game& game);

      void Render(float delta);
  };
}
