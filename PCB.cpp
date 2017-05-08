#include "PCB.h"
#include <iostream>
#include "MyProcess.h"


PCB::PCB(MyProcess* myProcess)
	:theProcess(myProcess)
{
	father = NULL;
	son = NULL;
	isReady = false;
}


PCB::~PCB(void)
{
}

bool PCB::applyForResource() {
	return true;
}

MyProcess* PCB::getProcess() {
	return theProcess;
}

PCB* PCB::getFather() {
	return father;
}

PCB* PCB::getSon() {
	return son;
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