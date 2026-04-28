cmake_minimum_required(VERSION 3.16)
project(Heap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML PATH (adjust this to your SFML folder's location)
set(CMAKE_PREFIX_PATH "D:/SFML-3.0.2")

# Find SFML 3.0
find_package(SFML 3.0 COMPONENTS
    Graphics
    Window
    System
    REQUIRED
)

# Add executable to HeapApp.exe
add_executable(HeapApp
    Heap_app.cpp

    src/Heap.cpp
    src/HeapController.cpp
    src/AnimationPlayer.cpp
    src/HeapRenderer.cpp
    src/UI.cpp
)

# Include headers 
target_include_directories(HeapApp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link SFML 
target_link_libraries(HeapApp
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

# Copy assets folder 
add_custom_command(TARGET HeapApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:HeapApp>/assets
)

# Copy SFML DLLs (Windows only) 
add_custom_command(TARGET HeapApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:HeapApp>
    $<TARGET_FILE_DIR:HeapApp>
    COMMAND_EXPAND_LISTS
)

# Copy assets folder
add_custom_command(TARGET HeapApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:HeapApp>/assets
)

# Copy data folder
add_custom_command(TARGET HeapApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data
    $<TARGET_FILE_DIR:HeapApp>/data
)