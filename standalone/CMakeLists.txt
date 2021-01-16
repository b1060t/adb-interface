project(adb-interface-standalone)

add_executable(adb_interface
	main.cpp
)

target_link_libraries(adb_interface
	component
	dom
	screen
)