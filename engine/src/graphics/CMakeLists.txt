add_library(engine_graphics STATIC)

target_sources(engine_graphics PRIVATE
    Camera.cpp
    Sprite.cpp
)

target_include_directories(engine_graphics PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)

target_link_libraries(engine_graphics PUBLIC
    MySDL
)