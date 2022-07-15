#ifndef TYPE_H
#define TYPE_H

#include "Util.h"

#include <vector>
#include <string>
#include <utility>
#include <iostream>

class Type
{
public:
	Type() = default;
	Type(const Type&);
	Type(Type&&);
	~Type();
public:
	void creatTmpType(const std::string&);
	std::string getTypeInfo()const;
	void setTypeInfo(const std::string &);
	void setNumber(const int);
	const int getNumber()const;
	void setFloatingNumber(const double);
	const double getFloatingNumber()const;
	void setString(const std::string&);
	const std::string getString()const;
	void setBool(const bool);
	const bool getBool()const;
	void setComplex(const std::vector<std::pair<std::string,Type>>&);
	const std::vector<std::pair<std::string,Type>> getComplex()const;
	const Type addComplex(const Type& ,const std::string&)const;
	const Type divComplex(const Type& ,const std::string&)const;
	const Type mulComplex(const Type& ,const std::string&)const;
	const Type minusComplex(const Type& ,const std::string&)const;
	const Type getComplexIndex(const std::string&)const;
public:
	Type& operator=(const Type&);
	Type& operator=(Type&&);
	const Type operator+(const Type&)const;
	const Type operator-(const Type&)const;
	const Type operator*(const Type&)const;
	const Type operator/(const Type&)const;
	Type& operator+=(const Type&);
	Type& operator-=(const Type&);
	Type& operator*=(const Type&);
	Type& operator/=(const Type&);
	bool operator<(const Type&)const;
	bool operator>(const Type&)const;
	bool operator==(const Type&)const;
	bool operator!=(const Type&)const;
	bool operator<=(const Type&)const;
	bool operator>=(const Type&)const;
	Type& operator++();
	Type operator++(int);
	Type& operator--();
	Type operator--(int);
private:
	const Type addNumber(const Type&)const;
	const Type addString(const Type&)const;
	const Type addFloatingNumber(const Type&)const;
	const Type mulNumber(const Type&)const;
	const Type mulFloatingNumber(const Type&)const;
	const Type divNumber(const Type&)const;
	const Type divFloatingNumber(const Type&)const;
	const Type minusNumber(const Type&)const;
	const Type minusFloatingNumber(const Type&)const;
	void clearType();
private:
	void *_ptr{};
	std::string _typeInfo{"Undifaind"};
};

std::ostream& operator<<(std::ostream& os, const Type& type);

#endif /* TYPE_H */
