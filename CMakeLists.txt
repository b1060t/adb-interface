cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON) #needed by ftxui
set(CXX_FLAGS
	-fno-short-wchar
)
project(adb_interface)

add_subdirectory(external/FTXUI)

include_directories(
	external/FTXUI
)

add_executable(test
	test.cpp
)

target_link_libraries(test
	component
	dom
	screen
)