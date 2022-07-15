#include "Type.h"

#include <iostream>
#include <vector>
#include <string>



Type::Type(const Type& other)
	:_typeInfo{other._typeInfo}
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (other._ptr)
	{
		if (_typeInfo == UTIL::TYPES::Numbers) { setNumber(other.getNumber()); }
		else if (_typeInfo == UTIL::TYPES::FloatingNumbers) { setFloatingNumber(other.getFloatingNumber()); }
		else if (_typeInfo == UTIL::TYPES::String) { setString(other.getString()); }
		else if (_typeInfo == UTIL::TYPES::Bool) { setBool(other.getBool()); }
		else if (_typeInfo == UTIL::TYPES::Complex) { setComplex(other.getComplex()); }
	}
}

Type::Type(Type&& other)
	:_typeInfo{other._typeInfo},_ptr{other._ptr}
{
	UTIL::print(__FUNCTION__,__LINE__);
	other._typeInfo.clear();
	other._ptr = nullptr;
}

Type::~Type()
{
	UTIL::print(__FUNCTION__,__LINE__);
	clearType();
}

inline std::string Type::getTypeInfo()const
{
	UTIL::print(__FUNCTION__,__LINE__);
	return _typeInfo;
}

inline void Type::setTypeInfo(const std::string& str)
{
	UTIL::print(__FUNCTION__,__LINE__);
	_typeInfo = str;
}

void Type::clearType()
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_ptr)
	{
		if (_typeInfo == UTIL::TYPES::Numbers) { delete static_cast<int*>(_ptr); }
		else if (_typeInfo == UTIL::TYPES::FloatingNumbers) { delete static_cast<double*>(_ptr); }
		else if (_typeInfo == UTIL::TYPES::String) { delete static_cast<std::string*>(_ptr); }
		else if (_typeInfo == UTIL::TYPES::Bool) { delete static_cast<bool*>(_ptr);}
		else if (_typeInfo == UTIL::TYPES::Complex) { delete static_cast<std::vector<std::pair<std::string,Type>>*>(_ptr);}
	}
}

void Type::setNumber(const int number)
{
	UTIL::print(__FUNCTION__,__LINE__);
	clearType();
	_typeInfo = UTIL::TYPES::Numbers;
	_ptr = static_cast<void*>(new int(number));
}

const int Type::getNumber()const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::Numbers)
	{
		return *(static_cast<int*>(_ptr));
	}
	return 0;
}

void Type::setFloatingNumber(const double d)
{
	UTIL::print(__FUNCTION__,__LINE__);
	clearType();
	_typeInfo = UTIL::TYPES::FloatingNumbers;
	_ptr = static_cast<void*>(new double(d));
}

const double Type::getFloatingNumber()const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::FloatingNumbers)
	{
		return *(static_cast<double*>(_ptr));
	}
	return 0;
}

void Type::setString(const std::string& str)
{
	UTIL::print(__FUNCTION__,__LINE__);
	clearType();
	_typeInfo = UTIL::TYPES::String;
	_ptr = static_cast<void*>(new std::string(str));
}

const std::string Type::getString()const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::String)
	{
		return *(static_cast<std::string*>(_ptr));
	}
	return {};
}

void Type::setBool(const bool b)
{
	UTIL::print(__FUNCTION__,__LINE__);
	clearType();
	_typeInfo = UTIL::TYPES::Bool;
	_ptr = static_cast<void*>(new bool(b));
}

const bool Type::getBool()const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::Bool)
	{
		return *(static_cast<bool*>(_ptr));
	}
	return 0;
}

void Type::setComplex(const std::vector<std::pair<std::string,Type>>& comp)
{
	UTIL::print(__FUNCTION__,__LINE__);
	clearType();
	_typeInfo = UTIL::TYPES::Complex;
	_ptr = static_cast<void*>(new std::vector<std::pair<std::string,Type>>(comp));
}

const std::vector<std::pair<std::string,Type>> Type::getComplex()const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::Complex)
	{
		return *(static_cast<std::vector<std::pair<std::string,Type>>*>(_ptr));
	}
	return {};
}

Type& Type::operator=(const Type& other)
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp(other);
	std::swap(tmp,*this);
	return *this;
}

Type& Type::operator=(Type&& other)
{
	UTIL::print(__FUNCTION__,__LINE__);
	clearType();
	_typeInfo = other._typeInfo;
	_ptr = other._ptr;
	other._ptr = nullptr;
	other._typeInfo.clear();
	return *this;
}

const Type Type::operator+(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return addNumber(other);}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) {return addFloatingNumber(other);}
	else if (UTIL::TYPES::String == getTypeInfo() && getTypeInfo() == other._typeInfo) {return addString(other);}
	throw std::invalid_argument(" don't give a inwalid argument ");
}

const Type Type::operator-(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return minusNumber(other);}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) {return minusFloatingNumber(other);}
	throw std::invalid_argument(" don't give a inwalid argument ");
}

const Type Type::operator*(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return mulNumber(other);}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) {return mulFloatingNumber(other);}
	throw std::invalid_argument(" don't give a inwalid argument ");
}

const Type Type::operator/(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return divNumber(other);}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) {return divFloatingNumber(other);}
	throw std::invalid_argument(" don't give a inwalid argument ");
}

Type& Type::operator+=(const Type& other)
{
	UTIL::print(__FUNCTION__,__LINE__);
	*this = operator+(other);
	return *this;
}

Type& Type::operator-=(const Type& other)
{
	UTIL::print(__FUNCTION__,__LINE__);
	*this = operator-(other);
	return *this;
}


Type& Type::operator*=(const Type& other)
{
	UTIL::print(__FUNCTION__,__LINE__);
	*this = operator*(other);
	return *this;
}

Type& Type::operator/=(const Type& other)
{
	UTIL::print(__FUNCTION__,__LINE__);
	*this = operator/(other);
	return *this;
}

bool Type::operator<(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return (*static_cast<int*>(_ptr) < *static_cast<int*>(other._ptr));}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) 
		{return (*static_cast<double*>(_ptr) < *static_cast<double*>(other._ptr));}
	else if (UTIL::TYPES::String == getTypeInfo() && getTypeInfo() == other._typeInfo) 
		{return (*static_cast<std::string*>(_ptr) < *static_cast<std::string*>(other._ptr));}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

bool Type::operator>(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return (*static_cast<int*>(_ptr) > *static_cast<int*>(other._ptr));}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) 
		{return (*static_cast<double*>(_ptr) > *static_cast<double*>(other._ptr));}
	else if (UTIL::TYPES::String == getTypeInfo() && getTypeInfo() == other._typeInfo) 
		{return (*static_cast<std::string*>(_ptr) > *static_cast<std::string*>(other._ptr));}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

bool Type::operator==(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return (*static_cast<int*>(_ptr) == *static_cast<int*>(other._ptr));}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) 
		{return (*static_cast<double*>(_ptr) == *static_cast<double*>(other._ptr));}
	else if (UTIL::TYPES::String == getTypeInfo() && getTypeInfo() == other._typeInfo) 
		{return (*static_cast<std::string*>(_ptr) == *static_cast<std::string*>(other._ptr));}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

bool Type::operator!=(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return (*static_cast<int*>(_ptr) != *static_cast<int*>(other._ptr));}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) 
		{return (*static_cast<double*>(_ptr) != *static_cast<double*>(other._ptr));}
	else if (UTIL::TYPES::String == getTypeInfo() && getTypeInfo() == other._typeInfo) 
		{return (*static_cast<std::string*>(_ptr) != *static_cast<std::string*>(other._ptr));}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

bool Type::operator<=(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return (*static_cast<int*>(_ptr) <= *static_cast<int*>(other._ptr));}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) 
		{return (*static_cast<double*>(_ptr) <= *static_cast<double*>(other._ptr));}
	else if (UTIL::TYPES::String == getTypeInfo() && getTypeInfo() == other._typeInfo) 
		{return (*static_cast<std::string*>(_ptr) <= *static_cast<std::string*>(other._ptr));}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

bool Type::operator>=(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::TYPES::Numbers == getTypeInfo() && getTypeInfo()== other._typeInfo) { return (*static_cast<int*>(_ptr) >= *static_cast<int*>(other._ptr));}
	else if (UTIL::TYPES::FloatingNumbers == getTypeInfo() && getTypeInfo()== other._typeInfo) 
		{return (*static_cast<double*>(_ptr) >= *static_cast<double*>(other._ptr));}
	else if (UTIL::TYPES::String == getTypeInfo() && getTypeInfo() == other._typeInfo) 
		{return (*static_cast<std::string*>(_ptr) >= *static_cast<std::string*>(other._ptr));}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

Type& Type::operator++()
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::Numbers)
	{
		++(*(static_cast<int*>(_ptr)));
		return *this;
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}
Type Type::operator++(int)
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::Numbers)
	{
		Type tmp (*this);
		--(*(static_cast<int*>(_ptr)));
		return tmp;
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

Type& Type::operator--()
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::Numbers)
	{
		--(*(static_cast<int*>(_ptr)));
		return *this;
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

Type Type::operator--(int)
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (_typeInfo == UTIL::TYPES::Numbers)
	{
		Type tmp (*this);
		--(*(static_cast<int*>(_ptr)));
		return tmp;
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

const Type Type::addNumber(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setNumber(getNumber()+ other.getNumber());
	return tmp;
}

const Type Type::addString(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setString(getString()+ other.getString());
	return tmp;
}

const Type Type::addFloatingNumber(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setFloatingNumber(getFloatingNumber()+ other.getFloatingNumber());
	return tmp;
}

const Type Type::mulNumber(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setNumber(getNumber() * other.getNumber());
	return tmp;
}

const Type Type::mulFloatingNumber(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setFloatingNumber(getFloatingNumber() * other.getFloatingNumber());
	return tmp;
}

const Type Type::divNumber(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setNumber(getNumber() / other.getNumber());
	return tmp;
}

const Type Type::divFloatingNumber(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setFloatingNumber(getFloatingNumber() / other.getFloatingNumber());
	return tmp;
}

const Type Type::minusNumber(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setNumber(getNumber() - other.getNumber());
	return tmp;
}

const Type Type::minusFloatingNumber(const Type& other)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	Type tmp ;
	tmp.setTypeInfo(getTypeInfo());
	tmp.setFloatingNumber(getFloatingNumber() - other.getFloatingNumber());
	return tmp;
}

const Type Type::addComplex(const Type& other, const std::string& typeName)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	std::vector<std::pair<std::string,Type>>* ptr = static_cast<std::vector<std::pair<std::string,Type>>*> (_ptr);
	for (int i = 0 ; i < ptr->size(); ++i)
	{
		if (typeName == (*ptr)[i].first)
		{
			return (*ptr)[i].second.operator+(other);
		}
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

const Type Type::divComplex(const Type& other, const std::string& typeName)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	std::vector<std::pair<std::string,Type>>* ptr = static_cast<std::vector<std::pair<std::string,Type>>*> (_ptr);
	for (int i = 0 ; i < ptr->size(); ++i)
	{
		if (typeName == (*ptr)[i].first)
		{
			return (*ptr)[i].second.operator/(other);
		}
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

const Type Type::mulComplex(const Type& other, const std::string& typeName)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	std::vector<std::pair<std::string,Type>>* ptr = static_cast<std::vector<std::pair<std::string,Type>>*> (_ptr);
	for (int i = 0 ; i < ptr->size(); ++i)
	{
		if (typeName == (*ptr)[i].first)
		{
			return (*ptr)[i].second.operator*(other);
		}
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

const Type Type::minusComplex(const Type& other, const std::string& typeName)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	std::vector<std::pair<std::string,Type>>* ptr = static_cast<std::vector<std::pair<std::string,Type>>*> (_ptr);
	for (int i = 0 ; i < ptr->size(); ++i)
	{
		if (typeName == (*ptr)[i].first)
		{
			return (*ptr)[i].second.operator-(other);
		}
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	
}

const Type Type::getComplexIndex(const std::string& str)const
{
	UTIL::print(__FUNCTION__,__LINE__);
	std::vector<std::pair<std::string,Type>>* ptr = static_cast<std::vector<std::pair<std::string,Type>>*> (_ptr);
	for (int i = 0 ; i < ptr->size(); ++i)
	{
		if (str == (*ptr)[i].first)
		{
			return (*ptr)[i].second;
		}
	}
	throw std::invalid_argument(" don't give a inwalid argument ");	

}

std::ostream& operator<<(std::ostream& os, const Type& type)
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (type.getTypeInfo() == UTIL::TYPES::Numbers)
	{
		os << type.getNumber();
	}
	else if (type.getTypeInfo() == UTIL::TYPES::FloatingNumbers)
	{
		os << type.getFloatingNumber();
	}
	else if (type.getTypeInfo() == UTIL::TYPES::String)
	{
		os << type.getString();
	}
	else if (type.getTypeInfo() == UTIL::TYPES::Bool)
	{
		os << type.getBool();
	}
	else if (type.getTypeInfo() == UTIL::TYPES::Complex)
	{
		auto it = type.getComplex();
		for (int i = 0 ; i < it.size() ; ++i)
		{
			os << it[i].first << "  " << it[i].second << std::endl;
		}
	}
	return os;
}

void Type::creatTmpType(const std::string& str)
{
	UTIL::print(__FUNCTION__,__LINE__);
	if (UTIL::isNumber(str))
	{
		this->setNumber(std::stoi(str));
		this->setTypeInfo(UTIL::TYPES::Numbers);
	}
	else if (UTIL::isFloatingNumber(str))
	{
		setFloatingNumber(std::stod(str));
		setTypeInfo(UTIL::TYPES::FloatingNumbers);
	}
	else if (UTIL::isBool(str))
	{
		setBool(str == "true");
		setTypeInfo(UTIL::TYPES::Bool);
	} else {
		setString(str);
		setTypeInfo(UTIL::TYPES::String);
	}
}

