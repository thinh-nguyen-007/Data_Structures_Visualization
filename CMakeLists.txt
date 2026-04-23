cmake_minimum_required(VERSION 3.16)

#project(LinkedListVisual LANGUAGES CXX) origin name, change to LinkedList to match name
project(LinkedList LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# assume SFML is directly inside D:/
set(CMAKE_PREFIX_PATH "Desktop:/SFML-3.0.2")

# Find SFML
find_package(SFML 3.0 COMPONENTS
    Graphics
    Window
    System
    REQUIRED
)

# Include subproject
add_subdirectory(LinkedList)
add_subdirectory(Visualization)
add_subdirectory(LinkedListCommand)