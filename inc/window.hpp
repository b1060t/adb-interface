#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "ftxui/component/component.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/button.hpp"

#include <utils.hpp>
#include <command.hpp>
#include <logger.hpp>

using namespace ftxui;

class MainWindow : public Component
{
public:
	MainWindow()
		:logger(49, 22, string("logcat")),
		output(49, 22, string("output"))
	{
		Add(&container_);
		container_.Add(&input);
		container_.Add(&output);
		container_.Add(&logger);
		input.placeholder = L"Command";
		input.on_enter = [&](){
			std::wstring str = input.content;
			SyncCommand cmd(string(str.begin(), str.end()));
			cmd.execute();
			output.getLog(cmd.getOutput());
		};
	}

	void getLog(string log)
	{
		logger.getLog(log);
	}

private:
	Container container_ = Container::Horizontal();
	Input input;
	LogDisplayer logger;
	LogDisplayer output;

	Element Render() override
	{
		return border(
			vbox({
				hbox({
					vcenter(bold(text(L" Input: "))),
					border(input.Render() | flex),
				}),
				separator(),
				hbox({
					output.RenderLog() | size(WIDTH, EQUAL, 49),
					logger.RenderLog() | size(WIDTH, EQUAL, 49),
				})
			})
		);
	}
};

#endif