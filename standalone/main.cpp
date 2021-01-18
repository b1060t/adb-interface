#include <iostream>
#include <fstream>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include <window.hpp>
#include <command.hpp>

using namespace ftxui;

int main(void) {
#if 0
	system("clear");
	auto screen = ScreenInteractive::FixedSize(60, 20);
	MainWindow component;
	screen.Loop(&component);

	return EXIT_SUCCESS;
#else
	std::cout << "Testing Delay Command:" << std::endl;
	getchar();
	DelayCommand dcmd(5000);
	dcmd.execute();

	std::cout << "Testing Sync Command 'ls -l':" << std::endl;
	getchar();
	SyncCommand scmd("ls -l");
	scmd.execute();
	std::cout << scmd.getOutput() << std::endl;
	getchar();

	std::cout << "Testing Async Command 'logcat':" << std::endl;
	getchar();
	AsyncCommand cmd(std::string("logcat"));
	cmd.execute();
	int i = 0;
	while(!cmd.isDone() && i <= 10)
	{
		std::cout << "Get trunk " << i++ << ". Length: " << cmd.getOutput().length() << ". Press 'Enter' to get next." <<std::endl;
		getchar();
		//std::cout << cmd.getOutput();
	}
	cmd.stop();
	std::cout << endl;

	return 0;
#endif
}