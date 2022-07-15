#include "Calculate.h"
#include "Type.h"
#include "typeControler.h"
#include "Util.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>



#ifndef ENGIN_H
#define ENGIN_H

class Engin{
public:
	Engin();
	void operator()(bool);
private:
	static void addVariable (Engin*, std::vector<std::string>&);
	static void print(Engin*, std::vector<std::string>&);
	static void conditionalStatements (Engin*, std::vector<std::string>&);
	static void loop (Engin*, std::vector<std::string> &);
	void exchengVariable (std::vector<std::string>&);
	std::vector<std::string> getTokens(const std::string &);
	Type getTmp(const std::string&);
	bool statments(std::vector<std::string>&);
	void skip();
	void p_b();
private:
	bool is_consol;
	Controler _typeControle;
	std::stringstream _forConvert;
	std::map<std::string,void(*)(Engin*,std::vector<std::string>&)>_myMap;
};/* End of class Engin */

#endif /* End of ENGIN_H */
