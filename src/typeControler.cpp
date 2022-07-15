#include "typeControler.h"
#include "Util.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>



void Controler::addVariable(const std::vector<std::string>& tokens)
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (tokens.size()<3)
	{
		_conMap[tokens[UTIL::TYPESDECLARATIONINFO::TypeName]];
		return ;
	}
	Type tmp;
	if (_conMap.find(tokens[UTIL::TYPESDECLARATIONINFO::TypeName]) != _conMap.end()) { throw std::invalid_argument("INVALID");}
	if (UTIL::isNumber(tokens[UTIL::TYPESDECLARATIONINFO::Parametrs]))
	{
		tmp.setNumber(std::stoi(tokens[UTIL::TYPESDECLARATIONINFO::Parametrs]));
	}
	else if (UTIL::isFloatingNumber(tokens[UTIL::TYPESDECLARATIONINFO::Parametrs]))
	{
		tmp.setFloatingNumber(std::stod(tokens[UTIL::TYPESDECLARATIONINFO::Parametrs]));
	}
	else if (UTIL::isBool(tokens[UTIL::TYPESDECLARATIONINFO::Parametrs]))
	{
		tmp.setBool(tokens[UTIL::TYPESDECLARATIONINFO::Parametrs] == "true");
	} else {
		tmp.setString(tokens[UTIL::TYPESDECLARATIONINFO::Parametrs]);
	}
	_conMap[tokens[UTIL::TYPESDECLARATIONINFO::TypeName]]= tmp;
}

Type& Controler::getVariable(const std::string& Name)
{
	UTIL::print(__FUNCTION__,__LINE__);
	return this->_conMap.at(Name);
}

const std::string Controler::getTypeInfo(const std::string& Name)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	return (_conMap.at(Name)).getTypeInfo();
}

void Controler::addComplex(std::vector<std::string>& tokens)
{
	UTIL::print(__FUNCTION__,__LINE__);
	std::vector<std::pair<std::string,Type>>tmp;
	std::vector<std::string>::iterator it = tokens.begin();
	while (it != tokens.end())
	{
		it = std::find(std::next(it),tokens.end(),std::string(":"));
		if (it != tokens.end())
		{
			Type t ;
			if (UTIL::isNumber(*(std::next(it))))
			{
				t.setNumber(std::stoi(*std::next(it)));
			}
			else if (UTIL::isFloatingNumber(*(std::next(it))))
			{
				t.setFloatingNumber(std::stod(*(std::next(it))));
			}
			else if (UTIL::isBool(*(std::next(it))))
			{
				t.setBool((*(std::next(it))) == "true");
			} else {
				t.setString(*(std::next(it)));
			}
			tmp.push_back(std::pair<std::string,Type>(*std::prev(it),t));
		}
	}
	Type t;
	t.setComplex(tmp);
	_conMap[tokens[UTIL::TYPESDECLARATIONINFO::TypeName]] = t;
}

Type& Controler::operator[](const std::string& Name)
{
	UTIL::print(__FUNCTION__,__LINE__);
	return this->_conMap[Name];
}
