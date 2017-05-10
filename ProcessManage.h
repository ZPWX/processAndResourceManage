#pragma once
/************************************************************************/
/* 进程调度管理：*/
/************************************************************************/

#include <string>

class PCB;
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
	//销毁进程，连同其子进程
	static bool destroy(PCB* pcb);
	//查找进程
	static PCB* find(std::string name);
	//Look process information
	static bool listProcess();
	//Clock interrupt	
	static bool timeInt();
	//Process schedule
	static void schedule();
	static void schedule(PCB* pcb);
	//添加进程进入阻塞队列
	static bool addBlockQueue(PCB* pcb);
	//添加进程进入就绪队列
	static bool addReadyQueue(PCB* pcb);
	//获取当前运行进程资源占用情况
	static void getRunningResource(int& amountA, int& amountB);

private:
	//优先级队列
	static PCB* queue0;
	static PCB* queue1;
	static PCB* queue2;
	//阻塞队列
	static PCB* blockQueue;
	static PCB* blockFirst;//阻塞队列首
	static PCB* blockLast;//阻塞队列尾
	//就绪队列
	static PCB* readyQueue;
	static PCB* readyFirst;//就绪队列首
	static PCB* readyLast;//就绪队列尾
	//当前正在运行的进程
	static PCB* runningProcess;
	//初始进程
	static PCB* initProcess;
};

