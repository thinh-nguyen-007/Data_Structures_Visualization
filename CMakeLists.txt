cmake_minimum_required(VERSION 3.16)
project(MyApp)

set(CMAKE_CXX_STANDARD 20)

# Collect sources (similar to wildcard)
file(GLOB_RECURSE SRC
    src/*.cpp
)

add_executable(run ${SRC})

# Include directories
target_include_directories(run PRIVATE
    assets
    include
    include/SceneManager
    include/Textures
    include/Drawing
    include/SceneManager/SnapShots
    include/SceneManager/Scenes
    src
    ${RAYLIB_DIR}/include
)

# Link directories (for raylib)
link_directories(${RAYLIB_DIR}/lib)

# Link libraries
target_link_libraries(run
    raylib
    opengl32
    gdi32
    winmm
    user32
)
