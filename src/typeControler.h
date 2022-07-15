#ifndef CONTROLER_H
#define CONTROLER_H

#include "Type.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>


class Controler
{
public:
	void addComplex(std::vector<std::string>&);
	void addVariable(const std::vector<std::string>&);
	Type& getVariable(const std::string&);
	Type& operator[](const std::string&);
	const std::string getTypeInfo(const std::string&)const;
private:
private:
	std::unordered_map<std::string,Type>_conMap{};
}; /* End of Controler */

#endif /* End of  CONTROLER_H*/
