cmake_minimum_required(VERSION 3.16)

project(HeapVisual LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where SFML is installed
set(CMAKE_PREFIX_PATH "D:/SFML-3.0.2")

# Find SFML
find_package(SFML 3.0 COMPONENTS
    Graphics
    Window
    System
    REQUIRED
)

# Include subproject
add_subdirectory(Heap)
add_subdirectory(VisualApp)
add_subdirectory(HeapController)
