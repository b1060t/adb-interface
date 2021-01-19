#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <utils.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui;
using namespace std;

class LogDisplayer : public Component
{
private:
	vector<string> _payload;
	long _xoffset, _yoffset;
	long _xlen, _ylen;
public:
	LogDisplayer(long xlen, long ylen)
	{
		_xlen = xlen;
		_ylen = ylen;
		_xoffset = 0;
		_yoffset = 0;
	}
	void getLog(string str)
	{
		istringstream ss(str);
		string tmp;
		while(getline(ss, tmp))
		{
			_payload.push_back(tmp);
		}
	}
	Element RenderLog()
	{
		Elements list;
		long len = _payload.size();
		//rewrite needed!!!
		for(long i = _payload.size() - _ylen - _yoffset; i < _payload.size() - _yoffset; i++)
		{
			len = _payload[i].length();
			len = min(len, _xlen);
			Element doc = hbox({
				text(buildwstring(_payload[i].substr(_xoffset, len))),
			}) | flex;
			list.push_back(doc);
		}
		if(list.empty()) list.push_back(text(L"empty"));
		return window(text(L"test"), vbox(list) | flex);
	}
	bool OnEvent(Event e)
	{
		if(!Focused()) return false;

		if(e == Event::ArrowUp) _yoffset++;
		if(e == Event::ArrowDown) _yoffset--;
		if(e == Event::ArrowRight) _xoffset++;
		if(e == Event::ArrowLeft) _xoffset--;

		_yoffset = _yoffset < 0 ? 0 : _yoffset;
		_yoffset = _payload.size() - _ylen - _yoffset < 0 ? _payload.size() + _ylen : _yoffset;
		_xoffset = _xoffset < 0 ? 0 : _xoffset;

		return true;
	}
};

#endif