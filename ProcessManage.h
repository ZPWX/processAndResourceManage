#pragma once
/************************************************************************/
/* 进程调度管理：*/
/************************************************************************/

#include <string>

class ProcessManage
{
public:
	ProcessManage(void);
	~ProcessManage(void);

	//Create init process
	static void init();
	//Create corresponding process
	static bool createProcess(std::string name, int priority);
	//Delete corresponding process
	static bool deleteProcess(std::string name);
	//Look process information
	static bool listProcess();
	//Clock interrupt	
	static bool timeInt();
};

