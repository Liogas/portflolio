add_executable(game
    src/main.cpp
    
    src/world/World.cpp
    
    src/computers/ComputerManager.cpp
    
    src/projects/ProjectManager.cpp

    src/ui/manager/UIManager.cpp
    src/ui/menus/computerMenu/ComputerUI.cpp
    src/ui/menus/pauseMenu/PauseMenuUI.cpp

    src/ui/widgets/Caroussel.cpp
    src/ui/widgets/ProjectCard.cpp
)

target_include_directories(game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(game PRIVATE
    engine
)