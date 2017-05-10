#include "Resource.h"


Resource::Resource(const int& amount)
	:amount(amount)
{
}


Resource::~Resource(void)
{
}

int Resource::getAmount() {
	return amount;
}