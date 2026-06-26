add_library(engine_map STATIC)

target_sources(engine_map PRIVATE
    MapParser.cpp
    TileMap.cpp
)

target_include_directories(engine_map PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)

target_link_libraries(engine_map PUBLIC
    tinyxml2
)