cmake_minimum_required(VERSION 3.20)

project(chip8 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW
add_subdirectory(external/glfw-3.5.1)

# GLAD
add_library(glad STATIC
    external/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)

# CHIP-8 executable
add_executable(chip8
    src/main.cpp
)

target_link_libraries(chip8 PRIVATE
    glfw
    glad
)

# OpenGL
find_package(OpenGL REQUIRED)

target_link_libraries(chip8 PRIVATE
    OpenGL::GL
)