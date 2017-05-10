#pragma once
class Resource
{
public:
	Resource(const int& amount);
	virtual ~Resource(void);

	int getAmount();

private:
	//资源总数量
	int amount;
};

