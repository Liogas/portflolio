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

target_include_directories(MySDL PUBLIC include)

find_package(SDL2 REQUIRED)

target_link_libraries(MySDL PUBLIC SDL2::SDL2)