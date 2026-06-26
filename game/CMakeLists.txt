add_executable(game
    src/main.cpp
    src/computers/ComputerManager.cpp
    src/projects/ProjectManager.cpp
)

target_include_directories(game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(game PRIVATE
    engine
)