#include <iostream>

#include "game.hpp"
#define VKFW_NO_INCLUDE_VULKAN_HPP
#include "vkfw/vkfw.hpp"
#include "glad/gl.h"

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
