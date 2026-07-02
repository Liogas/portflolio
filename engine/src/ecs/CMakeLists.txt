add_library(engine_ecs STATIC)

target_sources(engine_ecs PRIVATE

    systems/AnimationSystem.cpp
    systems/AnimationStateSystem.cpp
    systems/CollisionSystem.cpp
    systems/InputSystem.cpp
    systems/MovementSystem.cpp
    systems/RenderSystem.cpp
    systems/DebugRenderSystem.cpp
    systems/InteractionSystem.cpp
    systems/ComputerInteractionSystem.cpp

    events/InteractionModule.cpp

    factories/ComputerFactories.cpp
    factories/PlayerFactories.cpp
)

target_link_libraries(engine_ecs PUBLIC
    external
    MySDL
)

target_include_directories(engine_ecs PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)
