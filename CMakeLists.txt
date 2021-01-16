cmake_minimum_required(VERSION 3.4.1)

project(adb_interface)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON) #needed by ftxui
set(CXX_FLAGS )

add_subdirectory(external/FTXUI)

include_directories(
	external/FTXUI
	external/asio/asio/include
	inc
)

add_subdirectory(standalone)
add_subdirectory(client)