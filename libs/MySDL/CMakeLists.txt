add_library(MySDL STATIC)

target_sources(MySDL PRIVATE
    src/AnimationSDL.cpp
    src/AppSDL.cpp
    src/EventSDL.cpp
    src/InputSDL.cpp
    src/RendererSDL.cpp
    src/TextureSDL.cpp
    src/WindowSDL.cpp
)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

target_include_directories(MySDL
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_directories(MySDL
    PUBLIC
        ${SDL2_LIBRARY_DIRS}
        ${SDL2_IMAGE_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS}
)

target_link_libraries(MySDL
    PUBLIC
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
)