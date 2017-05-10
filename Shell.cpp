#include "Shell.h"

#include <iostream>
#include "Tool.h"
#include "ProcessManage.h"
#include "ResourceManage.h"


Shell::Shell(void)
{
	ProcessManage::init();
	instruck = NULL;
}


Shell::~Shell(void)
{
}

/************************************************************************/
/* 读取用户指令进行相应操作：
	input：用户输入的指令*/
/************************************************************************/
bool Shell::read(std::string s) {
	int input = 0;

	//对输入的指令进行分割解析
	instruck = new std::vector<std::string>;
	std::string delim = " ";//分隔符为空格
	Tool::split(s, delim, instruck);

	//获取命令
	std::string command = instruck->at(0);

	//匹配的同时进行指令参数检测（是否符合标准或个数是否匹配）
	//退出系统
	if(command == "q") {
		if(instruck->size() == 1) {
			return false;
		}
	}
	//创建进程
	else if(command == "cr") {
		//判断是否参数为两个，一个进程 ID,一个进程优先级
		if(instruck->size() != 3) {
			std::cout << ">>创建进程需提供进程名和优先级，请检查输入参数" << std::endl;
			std::cout << ">>";
		}
		else {
			std::string name = instruck->at(1);
			int priority = atoi(instruck->at(2).c_str());
			ProcessManage::createProcess(name, priority);
		}
	}
	//删除进程
	else if(command == "de") {
		//判断参数是否为一个，删除进程名
		if(instruck->size() != 2) {
			std::cout << ">>删除进程需提供进程名，请检查输入参数" << std::endl;
			std::cout << ">>";
		}
		else {
			std::string name = instruck->at(1);
			ProcessManage::deleteProcess(name);
		}
	}
	//申请资源
	else if(command == "req") {
		//判断参数是否为两个，资源名和申请资源数量
		if(instruck->size() != 3) {
			std::cout << ">>申请需提供资源名和数量，请检查输入参数" << std::endl;
			std::cout << ">>";
		}
		else {
			std::string name = instruck->at(1);
			int count = atoi(instruck->at(2).c_str());
			ResourceManage::requestResource();
		}
	}
	//释放资源
	else if(command == "rel") {
		//判断参数是否没有
		if(instruck->size() != 1) {
			std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
			std::cout << ">>";
		}
		else {
			ResourceManage::releaseResource();
		}
	}
	//时钟中断
	else if(command == "to") {
		if(instruck->size() != 1) {
			std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
			std::cout << ">>";
		}
		else {
			ProcessManage::timeInt();
		}
	}
	//查看进程信息
	else if(command == "list_p") {
		if(instruck->size() != 1) {
			std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
			std::cout << ">>";
		}
		else {
			ProcessManage::listProcess();
		}
	}
	//查看系统资源信息
	else if(command == "list_r") {
		if(instruck->size() != 1) {
			std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
			std::cout << ">>";
		}
		else {
			ResourceManage::listResource();
		}
	}
	//输入错误
	else {
		std::cout << ">>请检查输入，help查看指令输入帮助" << std::endl;
		std::cout << ">>";
	}

	//释放相应指针资源
	delete(instruck);

	return true;
}
