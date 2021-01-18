#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <utils.hpp>

using namespace std;


//rewrite with std::async?
class Command
{
protected:
	string _cmd;
	string _output;
	Command(string cmd)
		:_cmd(cmd) {}
	~Command() {}
	virtual void run() = 0;
public:
	virtual int execute() = 0;
	virtual string getOutput() = 0;
};

class SyncCommand : public Command
{
private:
	virtual void run() override
	{
		array<char, 128> buffer;
#ifdef __WIN32__	
		unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(_cmd.c_str(), "r"), _pclose);
#else
		unique_ptr<FILE, decltype(&pclose)> pipe(popen(_cmd.c_str(), "r"), pclose);
#endif
		if (!pipe)
		{
			_output = "execution failed";
		}
		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		{
			_output += buffer.data();
		}
	}
public:
	SyncCommand(string cmd)
		:Command(cmd) {}
	virtual int execute() override
	{
		run();
		return 0;
	}
	virtual string getOutput() override
	{
		return _output;
	}
};

class AsyncCommand : public Command
{
private:
	thread _thread;
	bool _stop;
	mutex _outputLock;
	virtual void run() override
	{
		array<char, 1024> buffer;
#ifdef __WIN32__
		unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(_cmd.c_str(), "r"), _pclose);
#else
		unique_ptr<FILE, decltype(&pclose)> pipe(popen(_cmd.c_str(), "r"), pclose);
#endif
		if (!pipe)
		{
			_output = "execution failed";
			_stop = true;
		}
		while(!_stop)
		{
			if(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
			{
				_outputLock.lock();
				_output += buffer.data();
				_outputLock.unlock();
			}
			else
			{
				_stop = true;
			}
		}
	}
public:
	AsyncCommand(string cmd)
		:Command(cmd) {}
	virtual int execute() override
	{
		_stop = false;
		_thread = thread(&AsyncCommand::run, this); //evoke an internal thread
		_thread.detach();
		return 0;
	}
	virtual string getOutput() override
	{
		string rst;
		_outputLock.lock();
		rst = _output;
		_output = "";
		_outputLock.unlock();
		return rst;
	}
	bool isDone()
	{
		return _stop;
	}
	void stop()
	{
		_stop = true;
	}
};

class DelayCommand : public Command
{
private:
	int _delayTime;
	virtual void run() override
	{
		Sleep(_delayTime);
	}
public:
	DelayCommand(int delayTime)
		:Command(""),
		_delayTime(delayTime) {}
	virtual int execute() override
	{
		run();
		return 0;
	}
	virtual string getOutput() override
	{
		return _output;
	}
};

class CommandList
{
private:
	vector<shared_ptr<Command>> _list;
public:
	CommandList() {}
	~CommandList() {}

	int push(shared_ptr<Command> cmd)
	{
		shared_ptr<Command> tmp = move(cmd);
		_list.push_back(tmp);
		return 0;
	}
	int executeByOrder()
	{
		for(auto c : _list)
		{
			c->execute();
		}
		return 0;
	}
};

#endif