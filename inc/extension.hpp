#ifndef EXTENSION_HPP
#define EXTENSION_HPP

#include <utils.hpp>
#include <logger.hpp>

struct CommandRegister
{
	string command;
	function<int(LogDisplayer&, vector<string>)> function;
	string description;
};

int IspHelp(LogDisplayer& logger, vector<string> params);
int IspVersion(LogDisplayer& logger, vector<string> params);

CommandRegister Reg[] = {
	{"isphelp",      IspHelp,      "isphelp"},
	{"ispversion",   IspVersion,   "ispversion"},
	{"ispinfo",      [](LogDisplayer& logger, vector<string> params){ logger.getLog("test"); return 0;},   "ispinfo"},
	{"setsmart",     [](LogDisplayer& logger, vector<string> params){ logger.getLog("test"); return 0;},   "setsmart"},
	{"getluma",      [](LogDisplayer& logger, vector<string> params){ logger.getLog("test"); return 0;},   "getluma"},
	{"shuttermode",  [](LogDisplayer& logger, vector<string> params){ logger.getLog("test"); return 0;},   "shuttermode"},
	{"shuttermin",   [](LogDisplayer& logger, vector<string> params){ logger.getLog("test"); return 0;},   "shuttermin"},
	{"shuttermax",   [](LogDisplayer& logger, vector<string> params){ logger.getLog("test"); return 0;},   "shuttermax"},
};

int IspHelp(LogDisplayer& logger, vector<string> params)
{
	logger.getLog(" ");
	logger.getLog("-----isp_test_help-----");
	for(auto c : Reg)
	{
		logger.getLog(c.command + "\n   desc: " + c.description);
	}
	logger.getLog(" ");
	return 0;
};

int IspVersion(LogDisplayer& logger, vector<string> params)
{
	logger.getLog(" ");
	logger.getLog("-----isp_test_version-----");
	logger.getLog(" ");
	logger.getLog("--printing all input params:");
	for(auto p : params)
	{
		logger.getLog(p);
	}
	logger.getLog("--end");
	logger.getLog(" ");
	return 0;
}

#endif