#include "ftxui/component/component.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/button.hpp"

#include <cstdio>
#include <codecvt>
#include <locale>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

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
		str = L"test";
		btn.on_click = [&](){
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
				//result += std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(buffer.data());
			}
			//std::wstring str(result.length(), L' ');
			str = std::wstring(10, L' ');
			std::copy(result.begin(), result.begin()+9, str.begin());
			//input.placeholder = str;
		};
	}

private:
	Container container_ = Container::Horizontal();
	Menu leftMenu;
	Menu rightMenu;
	Input input;
	Button btn;
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
				separator(),
				text(str),
			})
		);
	}
};