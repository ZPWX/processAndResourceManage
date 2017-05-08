#pragma once
/************************************************************************/
/* 进程类：*/
/************************************************************************/
#include <string>

class MyProcess
{
public:
	MyProcess(const std::string& theName, const int& thePriority, const int& resourceA,
		const int& resourceB);
	MyProcess(const std::string& theName, const int& thePriority);
	~MyProcess(void);

	std::string getName();
	void getResourceNeed(int& resource1, int& resource2);
	int getPriority();
	int getState();
	bool setState(const int& state);

private:
	std::string name;//进程名
	int resourceA, resourceB;//所需资源数量
	int priority;//进程优先级
	int state;//进程状态
};

