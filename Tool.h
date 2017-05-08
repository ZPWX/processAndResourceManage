#pragma once
/************************************************************************/
/* 工具类：提供通用的函数方法*/
/************************************************************************/

#include <string>
#include <vector>

class Tool
{
public:
	Tool(void);
	~Tool(void);

	//字符串分割
	static void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
	//新建进程资源数量随机数生成
	static int resourceRandom();

private:
	static bool rotate;//用于随机数生成时应用不同的随机数种子
};

