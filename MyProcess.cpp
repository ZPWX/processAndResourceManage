#include "MyProcess.h"
#include "Tool.h"


MyProcess::MyProcess(const std::string& theName, const int& thePriority, const int& resourceA,
	const int& resourceB)
	:name(theName),
	priority(thePriority),
	resourceA(resourceA),
	resourceB(resourceB)
{
}

MyProcess::MyProcess(const std::string& theName, const int& thePriority)
	:name(theName),
	priority(thePriority),
	resourceA(Tool::resourceRandom()),
	resourceB(Tool::resourceRandom())
{
}



MyProcess::~MyProcess(void)
{
}

std::string MyProcess::getName() {
	return name;
}

void MyProcess::getResourceNeed(int& resourceA, int& resourceB) {
	resourceA = this->resourceA;
	resourceB = this->resourceB;
}

int MyProcess::getPriority() {
	return priority;
}

int MyProcess::getState() {
	return state;
}

bool MyProcess::setState(const int& state) {
	this->state = state;
	return true;
}