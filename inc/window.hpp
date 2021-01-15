#include "ftxui/component/component.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/button.hpp"

#include <iostream>
#include <fstream>

using namespace ftxui;

class MainWindow : public Component
{
public:
	MainWindow()
	{
		Add(&container_);
		container_.Add(&leftMenu);
		container_.Add(&rightMenu);
		container_.Add(&input);
		container_.Add(&btn);
		leftMenu.entries = { L"a", L"b"};
		rightMenu.entries = { L"c", L"d"};
		input.placeholder = L"input";
		btn.label = L"ls";
		btn.on_click = [&](){

			system("ls"); // capture stdout
		};
	}

private:
	Container container_ = Container::Horizontal();
	Menu leftMenu;
	Menu rightMenu;
	Input input;
	Button btn;


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
				})
			})
		);
	}
};