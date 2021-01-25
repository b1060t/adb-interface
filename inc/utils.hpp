#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdio>
#include <codecvt>
#include <locale>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

#include <vector>
#include <sstream>
#include <algorithm>

#ifdef __WIN32__
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

using namespace std;

wstring buildwstring(string str)
{
	wstring result(str.length(), L' ');
	copy(str.begin(), str.end(), result.begin());
	return result;
}

wstring buildwstring(string str, int len)
{
	wstring result(len, L' ');
	copy(str.begin(), str.begin() + len - 1, result.begin());
	return result;
}

vector<string> splitByToken(string input, const char token)
{
	vector<string> params;
	istringstream ss(input);
	for(string param; getline(ss, param, token);)
	{
		params.push_back(param);
	}
	return params;
}

#endif