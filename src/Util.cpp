#include "Util.h"

#include <iostream>
#include <string>

//#define DEBAGER

void UTIL::print (const std::string& s , const int i)
{
#ifdef DEBAGER
	std::cout<< s << "  " << i << std::endl;
#endif 
}

bool UTIL::isNumber(const std::string& str)
{
	int i = (str[0] == '-') ? 1 : 0;
	for (; i < str.size() ; ++i)
	{
		if (!(str[i] <= '9' && str[i]>= '0'))
		{
			return false;
		}
	}
	return true;
}

bool UTIL::isFloatingNumber(const std::string& str)
{
	int dotcount{};
	int i = (str[0] == '-') ? 1 : 0;
	for (; i < str.size() ; ++i)
	{
		if (str[i] == '.')
		{
			++dotcount;
		}
		else if (!(str[i] <= '9' && str[i]>= '0'))
		{
			return false;
		}
	}
	if (dotcount == 1)
		return true;
	return false;
}

bool UTIL::isBool(const std::string& str)
{
	if (str == "true" || str == "false")
		return true;
	return false;
}
