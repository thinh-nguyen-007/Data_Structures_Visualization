# Heap/CMakeLists.txt

add_library(Heap
    src/Heap.cpp
)

target_include_directories(Heap
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)