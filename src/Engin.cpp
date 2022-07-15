#include "Engin.h"

#include <algorithm>
#include <iterator>

Engin::Engin()
	:_myMap{{UTIL::Kiwored::variable, Engin::addVariable}, 
		{UTIL::Kiwored::print, Engin::print},
		{UTIL::Kiwored::condKiw,conditionalStatements},
		{UTIL::Kiwored::loop,loop},}
		{
			UTIL::print(__FUNCTION__,__LINE__);
		}
void Engin::addVariable (Engin* th, std::vector<std::string>& tokens)
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (tokens.size() < 5)
	{
		if(tokens[UTIL::TYPESDECLARATIONINFO::Operator] == "{")
		{
			th->_typeControle.addComplex(tokens);
		} else {
			th->_typeControle.addVariable(tokens);
		}
	}
	else
	{
		
		if(tokens[UTIL::TYPESDECLARATIONINFO::Operator] == "{")
		{
			th->_typeControle.addComplex(tokens);
		}
		std::vector<std::string> tmp((tokens.begin()+3),tokens.end());
		Calculate c;
		tokens.erase((tokens.begin()+3),tokens.end());
		tokens.insert(tokens.begin()+3 ,c(th->_typeControle,tmp));
		addVariable(th,tokens);
	}
}

void Engin::exchengVariable (std::vector<std::string>& tokens)
{
		if(tokens.size() > 2 && tokens[1] == "=")
		{
			std::vector<std::string> tmp((tokens.begin()+2),tokens.end());
			Calculate c;
			tokens.erase((tokens.begin()+2),tokens.end());
			tokens.insert(tokens.begin()+2 ,c(_typeControle,tmp));
			_typeControle[tokens[0]] = getTmp(tokens[2]);
		}
}

void Engin::print(Engin* th, std::vector<std::string>& tokens)
{
	UTIL::print(__FUNCTION__,__LINE__);
	try
	{
		std::cout<< th->_typeControle.getVariable(tokens[1]) << std::endl;
	}
	catch(...)
	{
		for (int i = 1 ; i < tokens.size(); ++i)
			std::cout << tokens[i] << "  ";
		std::cout<< std::endl;
	}
}

void Engin::operator()(bool b)
{
	is_consol = b;
	UTIL::print(__FUNCTION__,__LINE__);
	std::string str;
	p_b();
	while(std::getline(std::cin, str))
	{
		auto tokens = getTokens(str);
		try{
			_myMap.at(tokens[0])(this,tokens);
		} catch (...)
		{
			exchengVariable(tokens);
		}
		p_b();
	}
}

std::vector<std::string> Engin::getTokens(const std::string & str)
{
	UTIL::print(__FUNCTION__,__LINE__);
	_forConvert << str;
	std::vector<std::string> tokens;
	while (!_forConvert.eof())
	{
		std::string tmp;
		_forConvert >> tmp;
		if (tmp != "")
			tokens.push_back(tmp);
	}
	_forConvert.clear();
	return tokens;
}

Type Engin::getTmp(const std::string& str)
{
	Type tmp;
	try{
		tmp =_typeControle.getVariable(str);
	}
	catch (...)
	{
		tmp.creatTmpType(str);	
	}
	return tmp;

}

bool Engin::statments(std::vector<std::string>& tokens)
{
	bool b = false;
	auto it = std::find_if( tokens.begin(), tokens.end(),[](const std::string& s)
				{
					return s == "<" || s == ">" || s == "==" || s == "!=" || s == ">=" || s == "<=";
				});
	if (it != tokens.end())
	{
		Type tmp = getTmp(*std::prev(it));
		Type tmp2 = getTmp(*std::next(it));
		std::string str = *it ;
		if (str == "<")
			b = tmp < tmp2;
		else if (str == ">")
			b = tmp > tmp2 ;
		else if (str == "==")
			b = tmp == tmp2;
		else if (str == "!=")
			b = tmp != tmp2;
		else if (str == "<=")
			b = tmp <= tmp2;
		else if (str == ">=")
			b = tmp >= tmp2;
	}
	return b;
}
void Engin::conditionalStatements (Engin* th, std::vector<std::string>& tokens)
{
	bool b = th->statments(tokens);
	if (b) { return; }
	th->skip();
	
}

void Engin::p_b()
{
	if(is_consol)
		std::cout<< "$";
}
void Engin::skip()
{
	int count{};
	do
	{
		std::string str;
		std::getline(std::cin,str);
		auto it = std::find_if(str.begin(),str.end(),[](const char& ch){
					return ch == '{' || ch == '}';
				});
		if(it == str.end()){continue;}
		else if (*it == '{')
		{
			count++;
		} else {
			count--;
		}
	}
	while (count != 0);
}

void Engin::loop (Engin* th, std::vector<std::string>& tokens)
{
	bool b = th->statments(tokens);
	if (!b) 
	{
		th->skip();
		return ;
	}
	std::vector<std::string> s;
	int count{};
	do
	{
		std::string str;
		std::getline(std::cin,str);
		s.push_back(str);
		auto it = std::find_if(str.begin(),str.end(),[](const char& ch){
					return ch == '{' || ch == '}';
				});
		if(it == str.end()){continue;}
		else if (*it == '{')
		{
			count++;
		} else {
			count--;
		}
	}
	while (count != 0);
	while (th->statments(tokens))
	{
		for (int j = 0 ; j < s.size() ; ++j)
		{
			auto i = th->getTokens(s[j]);
			try{
				th->_myMap.at(i[0])(th,i);
			}catch (...)
			{
				th->exchengVariable(i);
			}
		}
	}
}

