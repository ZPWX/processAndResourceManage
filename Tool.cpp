#include "Tool.h"


Tool::Tool(void)
{
}


Tool::~Tool(void)
{
}

/************************************************************************/
/* 字符串分割：
	s:源字符串
	delim:分割符
	ret:经过分割后返回的多个字符串*/
/************************************************************************/
void Tool::split(std::string& s, std::string& delim,std::vector< std::string >* ret)  
{  
	size_t last = 0;  
	size_t index=s.find_first_of(delim,last);  
	while (index!=std::string::npos)  
	{  
		ret->push_back(s.substr(last,index-last));  
		last=index+1;  
		index=s.find_first_of(delim,last);  
	}  
	if (index-last>0)  
	{  
		ret->push_back(s.substr(last,index-last));  
	}  
}  