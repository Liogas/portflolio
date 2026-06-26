add_library(engine_application STATIC)

target_sources(engine_application PRIVATE
    App.cpp
)

target_include_directories(engine_application PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)

target_link_libraries(engine_application PUBLIC
    engine_ecs
)