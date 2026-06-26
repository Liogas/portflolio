add_library(engine_systems STATIC)

target_sources(engine_systems PRIVATE
    systems/AnimationStateSystem.cpp
    systems/AnimationSystem.cpp
    systems/CollisionSystem.cpp
    systems/ComputerInteractionSystem.cpp
    systems/DebugRendererSystem.cpp
    systems/InputSystem.cpp
    systems/InteractionSystem.cpp
    systems/MovementSystem.cpp
    systems/RenderSystem.cpp
)

target_include_directories(engine_systems PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)