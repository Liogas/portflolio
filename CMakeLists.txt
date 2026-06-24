cmake_minimum_required(VERSION 3.16)

project(portfolio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# SDL2 via pkg-config (simple et efficace)
# =========================
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    includes
    includes/ui
    includes/ui/widgets
    includes/ui/factories
    includes/ui/style
    includes/ui/components
    includes/ecs/components
    includes/ecs/factories
    includes/ecs/world
    includes/ecs/systems
    includes/ecs/events
    srcs/ecs/registry
    srcs/ecs/systems
    srcs/ecs/components
    srcs/ecs/factories
    MySDL/includes
)

link_directories(
    ${SDL2_LIBRARY_DIRS}
    ${SDL2_IMAGE_LIBRARY_DIRS}
    ${SDL2_TTF_LIBRARY_DIRS}
)

# =========================
# Sources
# =========================

file(GLOB_RECURSE SOURCES
    srcs/*.cpp
    MySDL/srcs/*.cpp
)

# ⚠️ Si tu veux être plus strict, remplace GLOB par liste explicite
# (mais pour ton projet actuel, GLOB est OK)

# =========================
# Executable
# =========================

add_executable(portfolio ${SOURCES})

# =========================
# Link SDL
# =========================

target_link_libraries(portfolio
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

# =========================
# Warnings (équivalent de ton -Wall -Wextra -Werror)
# =========================

target_compile_options(portfolio PRIVATE
    -Wall -Wextra -Werror -g3
)