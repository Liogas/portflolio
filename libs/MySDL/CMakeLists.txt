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

target_include_directories(MySDL PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(MySDL
    PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
)