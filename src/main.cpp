#include <iostream>

#include "game.hpp"

int main() {
  try {
    ctn::Game game;
    game.loop();
    return 0;
  } catch (std::exception& ex) {
    std::cerr << "exception: " << ex.what() << std::endl;
    return 1;
  }
}
