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
#include <extension.hpp>

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
			wstring wstr = input.content;
			string str = string(wstr.begin(), wstr.end());
			vector<string> params = splitByToken(str, ' ');
			function<int(LogDisplayer&, vector<string>)> func;
			for(auto c : Reg)
			{
				if(params[0] == c.command)
				{
					func = c.function;
					break;
				}
			}
			if(func != nullptr) //costum command
			{
				func(output, params);
			}
			else //linux command
			{
				SyncCommand cmd(str);
				cmd.execute();
				output.getLog(cmd.getOutput());
			}
			input.content = L"";
		};
	}

	void getLog(string log)
	{
		logger.getLog(log);
	}

	function<void()> on_quit = [](){};
	bool OnEvent(Event e) override
	{
		if(e == Event::Escape)
		{
			on_quit();
			return true;
		}
		return Component::OnEvent(e);
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