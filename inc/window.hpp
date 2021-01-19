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
		:logger(100, 13)
	{
		Add(&container_);
		container_.Add(&leftMenu);
		container_.Add(&rightMenu);
		container_.Add(&input);
		container_.Add(&btn);
		container_.Add(&logger);
		leftMenu.entries = { L"a", L"b"};
		rightMenu.entries = { L"c", L"d"};
		input.placeholder = L"input";
		btn.label = L"ls";
		str = L"test";
		btn.on_click = [&](){
			SyncCommand cmd("ls");
			cmd.execute();
			str = buildwstring(cmd.getOutput(), 20);
		};
	}

	void getLog(string log)
	{
		logger.getLog(log);
	}

private:
	Container container_ = Container::Horizontal();
	Menu leftMenu;
	Menu rightMenu;
	Input input;
	Button btn;
	LogDisplayer logger;
	std::wstring str;

	Element Render() override
	{
		return border(
			vbox({
				hbox({
					vbox({
						hcenter(bold(text(L"一"))),
						separator(),
						leftMenu.Render(),
					}) | flex,
					separator(),
					vbox({
						hcenter(bold(text(L"二"))),
						separator(),
						rightMenu.Render(),
					}) | flex}
				),
				separator(),
				hbox({
					center(bold(text(L" Input: "))) | flex,
					border(input.Render() | flex)
				}),
				separator(),
				vbox({
					btn.Render()
				}),
				//separator(),
				//text(str),
				separator(),
				logger.RenderLog() | flex,
			})
		);
	}
};

#endif