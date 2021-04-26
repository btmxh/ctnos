#include "boot_state.hpp"

#include <fstream>
#include <iostream>

#include "../game.hpp"

ctn::BootState::BootState(Game& game)
    : State(game), m_rngEngine(std::random_device()()), m_rng(0.0f, 1.0f) {
  std::ifstream bootMessageFile("res/boot_message.txt");
  std::string line;
  while (std::getline(bootMessageFile, line)) {
    m_bootMessageLines.push_back(line);
  }
}

void ctn::BootState::Render(float delta) {
  float rngValue = m_rng(m_rngEngine);
  if (rngValue < delta) {
    m_printedLines++;
  }

  if (m_printedLines > m_bootMessageLines.size()) {
    m_game.SetCurrentState(m_game.GetDesktopState());
    return;
  }

  auto& nvg = m_game.GetNanoVG();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  nvgBeginFrame(nvg, 1280.0f, 720.0f, 1.0f);

  nvgBeginPath(nvg);

  nvgFontFace(nvg, Game::MONOSPACE_FONT);
  nvgFontSize(nvg, 20.0f);
  nvgFillColor(nvg, nvgRGBf(1.0f, 1.0f, 1.0f));

  float x = 10.0f, y = 30.0f;
  for (size_t i = 0; i < m_printedLines; i++) {
    const auto& line = m_bootMessageLines[i];
    nvgText(nvg, x, y, line.c_str(), nullptr);
    y += 20.0f;
  }

  nvgClosePath(nvg);

  nvgClosePath(nvg);
  nvgEndFrame(nvg);
}

