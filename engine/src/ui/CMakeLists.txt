add_library(engine_ui STATIC)

target_sources(engine_ui PRIVATE
    components/UIContainer.cpp
    components/UIPanel.cpp
    components/UIText.cpp

    manager/UIManager.cpp

    menus/computerMenu/ComputerUI.cpp
    menus/pauseMenu/PauseMenuUI.cpp

    widgets/Caroussel.cpp
    widgets/ProjectCard.cpp
)

target_include_directories(engine_ui PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)