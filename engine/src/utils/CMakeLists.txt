add_library(engine_utils STATIC)

target_sources(engine_utils PRIVATE
    CollisionUtils.cpp
)

target_include_directories(engine_utils PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)

target_link_libraries(engine_utils PUBLIC
    MySDL
)