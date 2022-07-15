#ifndef CALCULATE_H
#define CALCULATE_H

#include "Type.h"
#include "typeControler.h"

#include <iostream>
#include <vector>
#include <string>

struct Calculate
{
	std::string operator()(Controler&, std::vector<std::string>&)const;
	std::string divMul(Controler&, std::vector<std::string>&)const;
	std::string addMinus(Controler&, std::vector<std::string>&)const;
	std::string addTypes(Controler&, std::vector<std::string>&)const;
	std::string divTypes(Controler&, std::vector<std::string>&)const;
	std::string mulTypes(Controler&, std::vector<std::string>&)const;
	std::string minusTypes(Controler&, std::vector<std::string>&)const;
};/* End of struct Calculate */

#endif /* End of CALCULATE_H */
