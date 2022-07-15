#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>

namespace UTIL
{
	namespace TYPES
	{
		const std::string Numbers{"Numbers"};
		const std::string FloatingNumbers{"FloatingNumbers"};
		const std::string String{"String"};
		const std::string Bool{"Bool"};
		const std::string Complex{"Complex"};
	} /* End of TYPES */
	namespace TYPESDECLARATIONINFO
	{
		const int Specifayer{};
		const int TypeName{1};
		const int Operator{2};
		const int Parametrs{3};
	} /*  End of TYPESDECLARATIONINFO */
	namespace Kiwored
	{
		const std::string variable {"let"};
		const std::string condKiw {"if"};
		const std::string loop {"while"};
		const std::string print {"log"};
	}/* End of Kiwored */

	bool isBool(const std::string&);
	bool isNumber(const std::string&);
	bool isFloatingNumber(const std::string&);
	void print (const std::string& s , const int i);
}
#endif /* End of UTIL_H */
