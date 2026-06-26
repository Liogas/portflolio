cmake_minimum_required(VERSION 3.16)

add_subdirectory(src/ecs)
add_subdirectory(src/ui)
add_subdirectory(src/graphics)
add_subdirectory(src/map)
add_subdirectory(src/resources)
add_subdirectory(src/scene)
add_subdirectory(src/application)

# META TARGET (juste un agrégateur)
add_library(engine INTERFACE)

target_link_libraries(engine INTERFACE
    engine_application
    engine_ecs
    engine_ui
    engine_graphics
    engine_map
    engine_resources
    engine_scene
)