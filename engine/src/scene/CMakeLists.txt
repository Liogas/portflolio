add_library(engine_scene STATIC)

target_sources(engine_scene PRIVATE
    TestScene.cpp
)

target_include_directories(engine_scene PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)