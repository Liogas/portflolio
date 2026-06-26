add_library(engine_resources STATIC)

target_sources(engine_resources PRIVATE
    ResourceManager.cpp
)

target_include_directories(engine_resources PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)