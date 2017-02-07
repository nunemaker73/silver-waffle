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
#include <boost/property_tree/ptree.hpp>
#include "../CxxUrl/url.hpp"

namespace sec{

class xbrl {
private:
	Url xbrlUrl;
	boost::gregrorian::date dateFiled;
	std::string formType;
public:
	
}

class info {
private:
	boost::property_tree::ptree pt;
	/* 	getCIK does more than just load the CIK.
		It looks up SEC filing information and can 
		preload a property tree. It will go ahead and
		pull SIC */
	int getCIK(); // called after stock symbol is set
	std::vector<xbrl> xbrls;
public:
	std::string symbol;
	std::string CIK;
	std::string SIC;
	std::string SIC_desc;
	std::string company_name;
	info(string stock_symbol); 	// Constructor
	verify();
} // class sec
} // namespace sec
#end //!_SEC_H

