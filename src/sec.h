#ifndef _SEC_H
#define _SEC_H
/*
    Copyright (C) {2016}  {Craig Nunemaker}

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
	The following code was derived from sec-xbrl python code available on github at
	https://github.com/altova/sec-xbrl which was released under the apache 2,.0 license.
	the apache 2.0 license is compatible with GPL 3.
*/

#include <string>
#include "boost/property_tree/ptree.hpp"
#include "url.hpp"

namespace sec{

std::string urlPathQuery(Url u);

//connection class will connect and get stream ready for content parse
class connection{
private:
	boost::property_tree::ptree pt;
public:
	connection(std::string stock_name);
	connection(Url u);
	std::string getFact(std::string key){pt.get<std::string>(key);};
};


class report: private connection {
public:
	report(Url u):connection(u){};
}
class sec {
private:
	connection data;
	std::vector<report> reports;
public:
	std::string symbol;
	std::string CIK;
	std::string SIC;
	std::string SIC_desc;
	std::string company_name;
	info(std::string stock_symbol) :  symbol(stock_symbol),data(stock_symbol) {
		CIK=data.getFact("companyFilings.companyInfo.CIK");
		SIC=data.getFact("companyFilings.companyInfo.SIC");
		}; 	// Constructor
}; // class sec
} // namespace sec
#endif //!_SEC_H

