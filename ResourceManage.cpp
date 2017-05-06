#include <iostream>
#include "ResourceManage.h"


ResourceManage::ResourceManage(void)
{
}


ResourceManage::~ResourceManage(void)
{
}

/************************************************************************/
/* 申请系统资源：
	name:资源名
	count：申请资源数量*/
/************************************************************************/
bool ResourceManage::requestResource(std::string name, int count) {
	std::cout << ">>申请资源：" << name << "," << count << "个" << std::endl;

	return true;
}

/************************************************************************/
/* 释放对应资源：
	name：释放的资源名*/
/************************************************************************/
bool ResourceManage::releaseResource(std::string name) {
	std::cout << ">>释放资源：" << name << std::endl;

	return true;
}

/************************************************************************/
/* 查看系统资源信息：*/
/************************************************************************/
bool ResourceManage::listResource() {
	std::cout << ">>系统资源信息如下：" << std::endl;

	return true;
}