add_library(LinkedList
    src/LinkedList.cpp
)

target_include_directories(LinkedList
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)