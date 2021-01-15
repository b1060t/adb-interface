#include <iostream>
#include <fstream>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include <window.hpp>
//#include <asio.hpp>

using namespace ftxui;

int main(void) {
#if 1
	system("clear");
	auto screen = ScreenInteractive::FixedSize(60, 20);
	MainWindow component;
	screen.Loop(&component);

	return EXIT_SUCCESS;
#else
	std::cout << "aaa" << std::endl;
	return 0;
#endif
}