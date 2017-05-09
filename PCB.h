#pragma once
/************************************************************************/
/* 进程控制块：*/
/************************************************************************/

class MyProcess;
class PCB
{
public:
	PCB(MyProcess* myProcess);
	~PCB(void);

	//申请进程所需资源
	bool applyForResource();

	MyProcess* getProcess();
	PCB* getFather();
	bool setFather(PCB* pcb);
	PCB* getSon();
	bool setSon(PCB* pcb);
	PCB* getFore();
	bool setFore(PCB* const pcb);
	PCB* getNext();
	bool setNext(PCB* const pcb);
	bool getState();
	bool setState(bool state);

private:
	MyProcess* theProcess;//当前进程
	PCB* father;//父进程
	PCB* son;//子进程
	PCB* fore;//进程在队列中的上一个进程
	PCB* next;//进程在队列中的下一个进程
	bool isReady;//进程是否获得资源可以就绪
};

