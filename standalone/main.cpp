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
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen("ls", "r"), _pclose);
	if (!pipe)
	{
		result = "";
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		result += buffer.data();
	}
	std::wstring str(result.length(), L' ');
	std::copy(result.begin(), result.end(), str.begin());
	std::cout << "aaa" << std::endl;
	return 0;
#endif
}