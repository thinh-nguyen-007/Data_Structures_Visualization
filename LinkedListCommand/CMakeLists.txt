add_library(LinkedListCommand
    LinkedListCommand.cpp
)

target_include_directories(LinkedListCommand
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(LinkedListCommand
    PUBLIC
        LinkedList
)