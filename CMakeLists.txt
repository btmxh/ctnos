cmake_minimum_required(VERSION 3.12)

project(ctnos C CXX)

find_package(glfw3 REQUIRED)

add_library(glad
  glad/src/gl.c
)

target_include_directories(glad PUBLIC glad/include)

add_executable(ctnos
  src/main.cpp
)

target_include_directories(ctnos PUBLIC vkfw)
target_link_libraries(ctnos PUBLIC glad glfw)

