project(adb-interface-standalone)

include_directories(inc)
link_directories(lib)

add_executable(adb_interface
	main.cpp
)

target_link_libraries(adb_interface
	component
	dom
	screen
)