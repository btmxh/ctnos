#pragma once

namespace ctn {
class Game;

class State {
 public:
  explicit State(Game& game);
  virtual ~State();

  virtual void Render(float delta);

  virtual void Show();
  virtual void Hide();

  Game& GetGame();

 protected:
  Game& m_game;
};
}  // namespace ctn
