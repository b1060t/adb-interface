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
	string _name;
public:
	LogDisplayer(long xlen, long ylen, string name)
	{
		_xlen = xlen;
		_ylen = ylen;
		_xoffset = 0;
		_yoffset = 0;
		_name = name;
		for(int i = 0; i < _ylen; i++)
		{
			_payload.push_back(string(" "));
		}
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
		for(long i = _payload.size() - _ylen - _yoffset; i < _payload.size() - _yoffset; i++)
		{
			long len = _payload[i].length() - _xoffset;
			Element doc = len < 0
				? hbox({ text(L" ")}) | flex
				: hbox({ text(buildwstring(_payload[i].substr(_xoffset, min(len, _xlen))))}) | flex;
			list.push_back(doc);
		}
		return window(text(buildwstring(_name)), vbox(list) | flex);
	}
	bool OnEvent(Event e)
	{
		if(!Focused()) return false;

		if (ActiveChild() && ActiveChild()->OnEvent(e)) return true;

		bool _changed = false;
		if(e == Event::Character('w'))
		{
			_yoffset++;
			_changed = true;
		}
		if(e == Event::Character('s'))
		{
			_yoffset--;
			_changed = true;
		}
		if(e == Event::Character('d'))
		{
			_xoffset++;
			_changed = true;
		}
		if(e == Event::Character('a')){
			_xoffset--;
			_changed = true;
		}

		_yoffset = _yoffset < 0 ? 0 : _yoffset;
		_yoffset = _payload.size() - _ylen - _yoffset < 0 ? _payload.size() + _ylen : _yoffset;
		_xoffset = _xoffset < 0 ? 0 : _xoffset;

		return _changed;
	}
};

#endif