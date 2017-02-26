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

#include <string>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>
#include "connection.h"
#include "client.hpp"



sec::connection::connection(std::string stock_symbol)
{
	std::string urlstring;
	urlstring = "/index.html";//browse-edgar?action=getcompany&CIK="+stock_symbol+"&count=10&output=xml";
    https_client c("www.nunemakercpa.com", urlstring);
    std::string s;
	s=c.getContent();
	boost::property_tree::xml_parser::read_xml(s, pt);
}

sec::connection::connection(Url u)
{
	https_client c(u.host(),u.path_queries());
    std::string s;
	s=c.getContent();
	boost::property_tree::xml_parser::read_xml(s, pt);	
}