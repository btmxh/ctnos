#include "state.hpp"

ctn::State::State(ctn::Game& game) : m_game(game) {}

ctn::State::~State() {}

void ctn::State::Render(float delta) {}
void ctn::State::Show() {}
void ctn::State::Hide() {}

ctn::Game& ctn::State::GetGame() { return m_game; }

