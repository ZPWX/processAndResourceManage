#include "PCB.h"
#include <iostream>
#include "MyProcess.h"
#include "ResourceManage.h"


PCB::PCB(MyProcess* myProcess)
	:theProcess(myProcess)
{
	father = NULL;
	son = NULL;
	fore = NULL;
	next = NULL;
	isReady = false;
}


PCB::~PCB(void)
{
}

/************************************************************************/
/* 申请资源：
	isGet：是否申请资源时对资源数量进行相应的改变*/
/************************************************************************/
bool PCB::applyForResource(bool isGet) {
	int a = -1;
	int b = -1;
	theProcess->getResourceNeed(a, b);
	//进行资源申请
	if(ResourceManage::apply(a, b, isGet)) {
		return true;
	}
	else {
		return false;
	}
}

MyProcess* PCB::getProcess() {
	return theProcess;
}

PCB* PCB::getFather() {
	return father;
}

bool PCB::setFather(PCB* pcb) {
	father = pcb;
	return true;
}

PCB* PCB::getSon() {
	return son;
}

bool PCB::setSon(PCB* pcb) {
	son = pcb;
	return true;
}

PCB* PCB::getFore() {
	return fore;
}

bool PCB::setFore(PCB* const pcb) {
	fore = pcb;
	return true;
}

PCB* PCB::getNext() {
	return next;
}

bool PCB::setNext(PCB* const pcb) {
	next = pcb;
	return true;
}

bool PCB::getState() {
	return isReady;
}

bool PCB::setState(bool state) {
	isReady = state;
	return true;
}