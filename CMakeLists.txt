cmake_minimum_required(VERSION 3.16)
project(DataVisualizer)

set(CMAKE_CXX_STANDARD 20)

# USER PATHS (REQUIRED)
set(RAYLIB_DIR "" CACHE PATH "Path to raylib")
set(SFML_DIR "" CACHE PATH "Path to SFML")

if (NOT EXISTS "${RAYLIB_DIR}")
    message(FATAL_ERROR "Please set RAYLIB_DIR (e.g. -DRAYLIB_DIR=D:/raylib)")
endif()

if (NOT EXISTS "${SFML_DIR}")
    message(FATAL_ERROR "Please set SFML_DIR (e.g. -DSFML_DIR=D:/SFML-3.0.2)")
endif()

# GLOBAL VARIABLES
set(RAYLIB_INCLUDE "${RAYLIB_DIR}/include")
set(RAYLIB_LIB "${RAYLIB_DIR}/lib")

set(SFML_INCLUDE "${SFML_DIR}/include")
set(SFML_LIB "${SFML_DIR}/lib")

# LAUNCHER (RAYLIB)
file(GLOB SRC CONFIGURE_DEPENDS src/*.cpp)

add_executable(launcher ${SRC})

target_include_directories(launcher PRIVATE
    include
    ${RAYLIB_INCLUDE}
)

target_link_directories(launcher PRIVATE
    ${RAYLIB_LIB}
)

target_link_libraries(launcher PRIVATE
    raylib
    opengl32 gdi32 winmm user32
)

# SUBMODULES
add_subdirectory(Heap)
add_subdirectory(LinkedList)
add_subdirectory(Graph)
add_subdirectory(AVLTree)

# DLL COPYING (ONLY ONCE)
# SFML (use ONE SFML target: HeapApp)
add_custom_command(TARGET HeapApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SFML_DIR}/bin/*.dll
    ${CMAKE_BINARY_DIR}
)
# Raylib (from launcher)
if (EXISTS "${RAYLIB_DIR}/bin")
    add_custom_command(TARGET launcher POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${RAYLIB_DIR}/bin/*.dll
        ${CMAKE_BINARY_DIR}
    )
endif()
