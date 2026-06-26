cmake_minimum_required(VERSION 3.16)
project(portfolio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external)
add_subdirectory(libs/MySDL)
add_subdirectory(libs/tinyxml2)
add_subdirectory(engine)
add_subdirectory(game)