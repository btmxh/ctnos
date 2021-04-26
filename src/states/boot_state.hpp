#pragma once

#include <vector>
#include <string>
#include <random>

#include "state.hpp"

namespace ctn {
class BootState : public State {
 public:
  explicit BootState(Game& game);

  void Render(float delta);
 private:
  std::mt19937 m_rngEngine;
  std::uniform_real_distribution<float> m_rng;
  size_t m_printedLines = 0;
  std::vector<std::string> m_bootMessageLines;
};
}  // namespace ctn
