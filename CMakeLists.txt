cmake_minimum_required(VERSION 3.12)

project(ctnos C CXX)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_library(glad
  glad/src/gl.c
)

target_include_directories(glad PUBLIC glad/include)

add_library(nanovg
  external/nanovg/src/nanovg.c
)

target_include_directories(nanovg PUBLIC external/nanovg/src)

add_executable(ctnos
  src/graphics/nanovg.cpp
  src/states/boot_state.cpp
  src/states/desktop_state.cpp
  src/states/state.cpp
  src/game.cpp
  src/main.cpp
)

target_include_directories(ctnos PUBLIC external/vkfw/include)

target_link_libraries(ctnos PUBLIC glm glad glfw nanovg)

