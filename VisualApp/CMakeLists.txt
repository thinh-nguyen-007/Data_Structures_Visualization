# VisualApp/CMakeLists.txt
add_executable(VisualApp
    main.cpp
    UI.cpp
    HeapRenderer.cpp
    AnimationPlayer.cpp
)
target_link_libraries(VisualApp
    PRIVATE
        HeapController
        SFML::Graphics
        SFML::Window
        SFML::System
)
# copy assets
add_custom_command(TARGET VisualApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:VisualApp>/assets
)
# Copy SFML DLLs after build
add_custom_command(TARGET VisualApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:VisualApp>
    $<TARGET_FILE_DIR:VisualApp>
    COMMAND_EXPAND_LISTS
)