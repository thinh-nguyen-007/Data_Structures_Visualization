cmake_minimum_required(VERSION 3.16)
project(LinkedList LANGUAGES CXX)

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

# Add executable to LinkedListApp.exe
add_executable(LinkedListApp
    LinkedList_app.cpp

    src/LinkedList.cpp
    src/LinkedListCommand.cpp
    src/Animation.cpp
    src/LinkedListRenderer.cpp
    src/UI.cpp
)

# Include headers 
target_include_directories(LinkedListApp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link SFML 
target_link_libraries(LinkedListApp
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

# Copy assets folder 
add_custom_command(TARGET LinkedListApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:LinkedListApp>/assets
)

# Copy SFML DLLs (Windows only) 
add_custom_command(TARGET LinkedListApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:LinkedListApp>
    $<TARGET_FILE_DIR:LinkedListApp>
    COMMAND_EXPAND_LISTS
)

# Copy assets folder
add_custom_command(TARGET LinkedListApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:LinkedListApp>/assets
)

# Copy data folder
add_custom_command(TARGET LinkedListApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data
    $<TARGET_FILE_DIR:LinkedListApp>/data
)