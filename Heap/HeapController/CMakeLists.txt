add_library(HeapController
    HeapController.cpp
)

target_include_directories(HeapController
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(HeapController
    PUBLIC
        Heap
)