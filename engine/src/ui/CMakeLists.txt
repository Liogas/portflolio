add_library(engine_ui STATIC)

target_sources(engine_ui PRIVATE
    components/UIContainer.cpp
    components/UIPanel.cpp
    components/UIText.cpp
)

target_include_directories(engine_ui PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/src
)

target_link_libraries(engine_ui PUBLIC
    MySDL
    external
)