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
};

