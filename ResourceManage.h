#pragma once
/************************************************************************/
/* 系统资源管理：*/
/************************************************************************/

#include <string>

class Resource;
class PCB;
class ResourceManage
{
public:
	ResourceManage(void);
	~ResourceManage(void);

	//Apply for resource
	static bool requestResource();
	static bool apply(const int& countA, const int& countB, bool isGet);
	//Release resource
	static bool releaseResource();
	static bool releaseResource(PCB* pcb);
	//Look resource information
	static bool listResource();

private:
	static Resource* resourceA;                            //资源A
	static Resource* resourceB;                            //资源B
	static int remainA;                                    //资源A的剩余数量
	static int remainB;                                    //资源B的剩余数量
};

