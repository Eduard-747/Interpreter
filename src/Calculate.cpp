#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include "Calculate.h"


std::string Calculate::operator()(Controler& c, std::vector<std::string>& tokens)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	auto it = std::find(tokens.begin(),tokens.end(),"(");
	auto it2 = std::find(tokens.begin(),tokens.end(),")");
	if (it != tokens.end() && it2 != tokens.end())
	{
		std::vector<std::string> tmp(std::next(it),it2);
		auto forInsert = this->operator()(c,tmp);
		auto i = it;
		tokens.erase(it,std::next(it2));
		tokens.insert(i,forInsert);
		
	}
	return divMul(c,tokens);
}

std::string Calculate::divMul(Controler& c, std::vector<std::string>& tokens)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	auto it = std::find_if(tokens.begin(),tokens.end(),[&](const std::string& s){
				return s == "*" || s == "/";
			});
	if(it == tokens.end())
	{
		return addMinus(c,tokens);
	}
	else if (*it == "*")
	{
		return mulTypes(c,tokens);
	}else{
		return divTypes(c,tokens);
	}
}

std::string Calculate::addMinus(Controler& c, std::vector<std::string>& tokens)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	auto it = std::find_if(tokens.begin(),tokens.end(),[&](const std::string& s){
				return s == "+" || s == "-";
			});
	if(it == tokens.end())
	{
		return tokens[0];
	}
	else if (*it == "+")
	{
		return addTypes(c,tokens);
	}else{
		return minusTypes(c,tokens);
	}

}

std::string Calculate::mulTypes(Controler& c, std::vector<std::string>& tokens)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	auto it = tokens.begin();
	while (it != tokens.end())
	{
		it = std::find(it,tokens.end(),"*");
		if (it != tokens.end())
		{
			Type first;
			try{
				first = c.getVariable(*std::prev(it));
			}catch(...){
				first.creatTmpType((*std::prev(it)));
			}
			Type second;
			try{
				second = c.getVariable(*std::next(it));
			}catch(...){
				second.creatTmpType(*std::next(it));
			}
			Type res = first*second;
			auto tmp2 = std::prev(it);
			auto tmp = it;
			tokens.erase(std::prev(tmp),std::next(tmp,2));
			if (res.getTypeInfo() == UTIL::TYPES::Numbers)
				tokens.insert(tmp2,std::to_string(res.getNumber()));
			else if (res.getTypeInfo() == UTIL::TYPES::FloatingNumbers)
				tokens.insert(tmp2,std::to_string(res.getFloatingNumber()));
			else if (res.getTypeInfo() == UTIL::TYPES::Bool)
				tokens.insert(tmp2,std::to_string(res.getBool()));
			else 
				tokens.insert(tmp2,res.getString());
		}
	}
	return divTypes(c,tokens);
}

std::string Calculate::divTypes(Controler& c, std::vector<std::string>& tokens)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	auto it = tokens.begin();
	while (it != tokens.end())
	{
		it = std::find(it,tokens.end(),"/");
		if (it != tokens.end())
		{
			Type first;
			try{
				first = c.getVariable(*std::prev(it));
			}catch(...){
				first.creatTmpType((*std::prev(it)));
			}
			Type second;
			try{
				second = c.getVariable(*std::next(it));
			}catch(...){
				second.creatTmpType(*std::next(it));
			}
			Type res = first/second;
			auto tmp = it ;
			auto tmp2 = std::prev(it);
			tokens.erase(std::prev(tmp),std::next(tmp,2));
			if (res.getTypeInfo() == UTIL::TYPES::Numbers)
				tokens.insert(tmp2,std::to_string(res.getNumber()));
			else if (res.getTypeInfo() == UTIL::TYPES::FloatingNumbers)
				tokens.insert(tmp2,std::to_string(res.getFloatingNumber()));
			else if (res.getTypeInfo() == UTIL::TYPES::Bool)
				tokens.insert(tmp2,std::to_string(res.getBool()));
			else 
				tokens.insert(tmp2,res.getString());
		}
	}
	return addMinus(c,tokens);
}

std::string Calculate::addTypes(Controler& c, std::vector<std::string>& tokens)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	auto it = tokens.begin();
	while (it != tokens.end())
	{
		it = std::find(it,tokens.end(),"+");
		if (it != tokens.end())
		{
			Type first;
			try{
				first = c.getVariable(*std::prev(it));
			}catch(...){
				first.creatTmpType((*std::prev(it)));
			}
			Type second;
			try{
				second = c.getVariable(*std::next(it));
			}catch(...){
				second.creatTmpType(*std::next(it));
			}
			Type res = first+second;
			auto tmp = it ;
		       	auto tmp2 = std::prev(it);
			tokens.erase(std::prev(tmp),std::next(tmp,2));
			if (res.getTypeInfo() == UTIL::TYPES::Numbers)
				tokens.insert(tmp2,std::to_string(res.getNumber()));
			else if (res.getTypeInfo() == UTIL::TYPES::FloatingNumbers)
				tokens.insert(tmp2,std::to_string(res.getFloatingNumber()));
			else if (res.getTypeInfo() == UTIL::TYPES::Bool)
				tokens.insert(tmp2,std::to_string(res.getBool()));
			else 
				tokens.insert(tmp2,res.getString());
		}
	}
	return minusTypes(c,tokens);
}

std::string Calculate::minusTypes(Controler& c, std::vector<std::string>& tokens)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	auto it = tokens.begin();
	while (it != tokens.end())
	{
		it = std::find(it,tokens.end(),"-");
		if (it != tokens.end())
		{
			Type first;
			try{
				first = c.getVariable(*std::prev(it));
			}catch(...){
				first.creatTmpType((*std::prev(it)));
			}
			Type second;
			try{
				second = c.getVariable(*std::next(it));
			}catch(...){
				second.creatTmpType(*std::next(it));
			}
			Type res = first-second;
			auto tmp = it ;
		       	auto tmp2 = std::prev(it);
			tokens.erase(std::prev(tmp),std::next(tmp,2));
			if (res.getTypeInfo() == UTIL::TYPES::Numbers)
				tokens.insert(tmp2,std::to_string(res.getNumber()));
			else if (res.getTypeInfo() == UTIL::TYPES::FloatingNumbers)
				tokens.insert(tmp2,std::to_string(res.getFloatingNumber()));
			else if (res.getTypeInfo() == UTIL::TYPES::Bool)
				tokens.insert(tmp2,std::to_string(res.getBool()));
			else 
				tokens.insert(tmp2,res.getString());
		}
	}
	return addMinus(c,tokens);
}
