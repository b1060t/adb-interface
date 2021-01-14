#include <iostream>
#include <fstream>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

int main(void) {
#if 1
	using namespace ftxui;

	auto document =  //
		vbox({
			gauge(0.5)
	});

	document = document | size(WIDTH, LESS_THAN, 80);

	auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
	Render(screen, document);

	std::cout << screen.ToString() << std::endl;
	//std::fstream file("1.txt", std::ios::out);
	//file << screen.ToString();
	//file.close();
	std::cout << screen.PixelAt(0,1).character << std::endl;

	return EXIT_SUCCESS;
#else
	std::cout << "aaa" << std::endl;
	return 0;
#endif
}