cmake_minimum_required(VERSION 3.20)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)
project(GraphLibrary CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent for Raylib
include(FetchContent)
if(NOT TARGET raylib)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

# Collect source files
file(GLOB_RECURSE LIB_SRC "src/*.cpp")

# Define the GraphCore library, including Graph_app.cpp explicitly
add_library(GraphCore STATIC ${LIB_SRC} "Graph_app.cpp")

# Export include paths
target_include_directories(GraphCore PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link to Raylib
target_link_libraries(GraphCore PUBLIC raylib)