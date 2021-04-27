cmake_minimum_required(VERSION 3.12)

project(ctnos C CXX)

set(CMAKE_CXX_STANDARD 17)

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
  src/common/rect.cpp
  src/window/window.cpp
  src/window/desktop_window.cpp
  src/window/window_manager.cpp
  src/graphics/nanovg.cpp
  src/states/boot_state.cpp
  src/states/desktop_state.cpp
  src/states/state.cpp
  src/game.cpp
  src/main.cpp
)

target_include_directories(ctnos PUBLIC external/vkfw/include)
target_include_directories(ctnos PUBLIC ${GLM_INCLUDE_DIRS})

target_link_libraries(ctnos PUBLIC glad glfw nanovg)

