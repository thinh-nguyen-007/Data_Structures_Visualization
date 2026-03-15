add_executable(VisualApp
    main.cpp
    UI.cpp
 "HeapModel.cpp")
target_include_directories(VisualApp PRIVATE
    ${CMAKE_SOURCE_DIR}/Heap/include
)
target_link_libraries(VisualApp
    PRIVATE
        Heap
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