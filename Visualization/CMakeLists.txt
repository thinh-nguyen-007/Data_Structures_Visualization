add_executable(Visualization
    main.cpp
    UI.cpp
    LinkedListRenderer.cpp
    Animation.cpp
)

set_target_properties(Visualization PROPERTIES
    BUILD_RPATH "@executable_path"
)

target_link_libraries(Visualization
    PRIVATE
        LinkedListCommand
        SFML::Graphics
        SFML::Window
        SFML::System
)

# Copy SFML DLLs after build

if(WIN32)
	add_custom_command(TARGET Visualization POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_RUNTIME_DLLS:Visualization>
		$<TARGET_FILE_DIR:Visualization>
		COMMAND_EXPAND_LISTS
	)
elseif(APPLE)
	add_custom_command(TARGET Visualization POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		/usr/local/lib/
		$<TARGET_FILE_DIR:Visualization>
	)
endif()