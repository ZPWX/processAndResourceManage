#include <iostream>
#include "ProcessManage.h"
#include "MyProcess.h"
#include "PCB.h"

PCB* ProcessManage::queue0 = NULL;
PCB* ProcessManage::queue1 = NULL;
PCB* ProcessManage::queue2 = NULL;

PCB* ProcessManage::blockQueue = NULL;
PCB* ProcessManage::blockFirst = NULL;
PCB* ProcessManage::blockLast = NULL;

PCB* ProcessManage::readyQueue = NULL;
PCB* ProcessManage::readyFirst = NULL;
PCB* ProcessManage::readyLast = NULL;

ProcessManage::ProcessManage(void)
{
}


ProcessManage::~ProcessManage(void)
{
}


/************************************************************************/
/* 初始化进程：创建初始进程*/
/************************************************************************/
void ProcessManage::init() {
	MyProcess* process = new MyProcess("initProcess", 1, 0, 0);
	PCB* pcb = new PCB(process);
	pcb->setState(true);                                      //设置状态为就绪
	pcb->getProcess()->setState(1);                           //设置进程状态为运行
	queue0 = pcb;
	std::cout << ">>系统进程 " << queue0->getProcess()->getName() << " 已创建运行" << std::endl;
	std::cout << ">>系统已启动，请输入相应指令进行操作" << std::endl;
	std::cout << ">>";
}


/************************************************************************/
/* 创建进程：
	name：新建进程名
	priority：新建进程优先级*/
/************************************************************************/
bool ProcessManage::createProcess(std::string name, int priority) {
	int rA = -1;
	int rB = -1;

	MyProcess* process = new MyProcess(name, priority);
	process->getResourceNeed(rA, rB);
	PCB* pcb = new PCB(process);

	std::cout << ">>进程： " << name << " 创建成功，优先级为：" << priority 
		<< " 资源A、B需求量为:" << rA << "、" << rB  << std::endl;

	addReadyQueue(pcb);                                  //新建进程后将其添加入就绪队列

	std::cout << ">>";

	return true;
}

/************************************************************************/
/* 删除进程：
	name：删除的进程名*/
/************************************************************************/
bool ProcessManage::deleteProcess(std::string name) {
	std::cout << ">>进程： " << name << " 删除成功" << std::endl;
	std::cout << ">>";

	return true;
}

/************************************************************************/
/* 查看进程列表：*/
/************************************************************************/
bool ProcessManage::listProcess() {
	std::cout << ">>进程列表如下：" << std::endl;

	return true;
}

/************************************************************************/
/* 时钟中断：*/
/************************************************************************/
bool ProcessManage::timeInt() {
	std::cout << ">>时钟中断" << std::endl;

	return true;
}

/************************************************************************/
/* 进程调度：*/
/************************************************************************/
void ProcessManage::schedule() {

}

void ProcessManage::schedule(PCB* pcb) {
	//首先对需要调度的进程的资源进行申请
	pcb->applyForResource();

	//如果进程是资源准备不足则进入阻塞队列
	if(!pcb->getState()) {
		addBlockQueue(pcb);
	}
	//如果进程资源已获得则进入就绪队列
	else {
		addReadyQueue(pcb);
	}
}

bool ProcessManage::addBlockQueue(PCB* pcb) {
	return true;
}

/************************************************************************/
/* 添加进程进入就绪队列：
	pcb：添加的进程*/
/************************************************************************/
bool ProcessManage::addReadyQueue(PCB* pcb) {
	if(readyQueue == NULL) {                          //如果当前就绪队列中没有进程
		if(pcb->applyForResource()) {                 //如果进程的资源申请成功则进入就绪队列运行
			readyQueue = pcb;                         //进入就绪队列
			readyLast = pcb;                          //同时它也是队尾进程
			pcb->getProcess()->setState(1);           //设置进程为运行状态

			std::cout << ">>当前无运行进程，进程分配资源成功，直接运行进程" << std::endl;
		}
		else {                                        //如果资源不足则进程阻塞进入阻塞队列
			addBlockQueue(pcb);
			std::cout << ">>当前无运行进程，进程分配资源失败，进程阻塞队列" << std::endl;
		}
	}
	//如果就绪队列不为空，对新加入的进程做一次优先级检查，如果进程优先级高则取代当前运行进程
	else {
		if(readyQueue->getProcess()->getPriority() > pcb->getProcess()->getPriority()) {

			std::cout << ">>当前进程：" << pcb->getProcess()->getName() << " 比当前运行进程 "
				<< readyQueue->getProcess()->getName() << " 高" << std::endl;

			if(pcb->applyForResource()) {                        //如果进程的资源申请成功则插队运行
				PCB* currentProcess = readyQueue;                //获取当前运行进程
				currentProcess->getProcess()->setState(0);       //设置当前运行进程为就绪不运行
				readyQueue = pcb;                                //将新进程插入队首
				pcb->setNext(currentProcess);                    //队首进程指向下一个进程（被插队的进程）
				pcb->getProcess()->setState(1);                  //设置进程为运行状态

				std::cout << ">>当前进程分配资源成功，直接运行进程" << std::endl;
			}
			else {                                               //如果资源不足则进程阻塞进入阻塞队列
				addBlockQueue(pcb);

				std::cout << ">>当前进程分配资源失败，进程阻塞队列" << std::endl;
			}
		}
		//如果进程优先级没有当前运行进程高，则插入就绪进程队尾
		else {
			PCB* lastProcess = readyLast;                        //获取就绪队列最尾部进程
			lastProcess->setNext(pcb);                           //插入队尾
			readyLast = pcb;                                     //使就绪队列队尾指针指向这个新加入队尾的进程

			std::cout << ">>当前进程：" << pcb->getProcess()->getName() << " 比当前运行进程 "
				<< readyQueue->getProcess()->getName() << " 低,加入就绪队列" << std::endl;
		}
	}

	return true;
}