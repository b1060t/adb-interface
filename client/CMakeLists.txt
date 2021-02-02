project(adb-interface-client)

include_directories(inc)

add_executable(client
	socket.cpp
)

target_link_libraries(client
	component
	dom
	screen
)