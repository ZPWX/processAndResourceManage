#include <iostream>
#include "ResourceManage.h"
#include "Resource.h"
#include "ResourceA.h"
#include "ResourceB.h"
#include "ProcessManage.h"
#include "PCB.h"
#include "MyProcess.h"

Resource* ResourceManage::resourceA = new ResourceA();
Resource* ResourceManage::resourceB = new ResourceB();
int ResourceManage::remainA = resourceA->getAmount();
int ResourceManage::remainB = resourceB->getAmount();

ResourceManage::ResourceManage(void)
{
}


ResourceManage::~ResourceManage(void)
{
}

/************************************************************************/
/* 申请系统资源：
/************************************************************************/
bool ResourceManage::requestResource() {
	//std::cout << ">>申请资源：" << name << std::endl;
	ProcessManage::schedule();

	return true;
}

bool ResourceManage::requestResource(std::string name) {
	//std::cout << ">>申请资源：" << name << std::endl;
	ProcessManage::schedule();

	return true;
}

bool ResourceManage::requestResource(std::string name, int count) {
	std::cout << ">>申请资源：" << name << "," << count << "个" << std::endl;

	return true;
}

/************************************************************************/
/* 进程资源申请，申请成功则资源数量进行相应的变化:
	countA:资源A的申请数量
	countB:资源B的申请数量
	isGet:是否是资源数量进行相应的变化*/
/************************************************************************/
bool ResourceManage::apply(const int& countA, const int& countB, bool isGet) {
	if(countA <= remainA && countB <= remainB) {
		if(isGet) {
			remainA -= countA;
			remainB -= countB;
		}
		return true;
	}

	return false;
}

/************************************************************************/
/* 释放对应资源：
/************************************************************************/
bool ResourceManage::releaseResource() {
	//获取当前运行进程的资源数目,并释放
	int runA = -1;
	int runB = -1;
	ProcessManage::getRunningResource(runA, runB);
	remainA += runA;
	remainB += runB;

	//重新调度进程
	ProcessManage::schedule();

	return true;
}

/************************************************************************/
/* 释放对应资源：
	pcb:要释放资源的进程*/
/************************************************************************/
bool ResourceManage::releaseResource(PCB* pcb) {
	//检测此进程是否有占用资源,没有资源占用直接返回
	if(!pcb->getState()) {
		return false;
	}

	//获取当前运行进程的资源数目,并释放
	int runA = -1;
	int runB = -1;
	pcb->getProcess()->getResourceNeed(runA, runB);
	remainA += runA;
	remainB += runB;

	std::cout << ">>进程 " << pcb->getProcess()->getName() << " 资源释放成功" << std::endl;

	return true;
}

/************************************************************************/
/* 查看系统资源信息：*/
/************************************************************************/
bool ResourceManage::listResource() {
	std::cout << ">>系统资源信息如下：" << std::endl;
	std::cout << "ResourceA:amount=" << resourceA->getAmount() << " remain=" << remainA << std::endl;
	std::cout << "ResourceB:amount=" << resourceB->getAmount() << " remain=" << remainB << std::endl;

	return true;
}