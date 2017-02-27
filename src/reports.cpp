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
#include <iterator>
#include <boost/property_tree/xml_parser.hpp>
#include "sec.hpp"
#include "client_https.hpp"



sec::report::report(std::string stock_symbol)
{
	using SimpleWeb::HTTPS;
	//using xercesc;
	std::string urlstring;
	urlstring = "/cgi-bin/browse-edgar?action=getcompany&CIK="+stock_symbol+"&count=10&output=xml";
    SimpleWeb::Client<HTTPS> c("www.sec.gov");
    std::shared_ptr<SimpleWeb::Client<HTTPS>::Response> response_p;
    std::cout << urlstring<<"\n";
    response_p = c.request("GET",urlstring);
	std::cout  << response_p->http_version <<"\t" << response_p->status_code<<"\n";
	//std::cout << response_p->content.rdbuf();

	std::string data(std::istream_iterator<char>(response_p->content),std::istream_iterator<char>());
	std::cout << data;
//	try { XMLPlatformUtils::Initialize();}
//      catch (const XMLException& toCatch) {std::cout<<toCatch.what()<<"\n";}
//    DOMImplementation * impl = DOMImplementation::getImplementation();
//    DOMLSParser *parser = (DOMImplementationLS*)impl)->createLSParser(DOMImplementation::MODE_SYNCHRONOUS, 0);
//    DOMDocument *doc;
    
//    Wrapper4InputSource source (new xMemBufInputSource((const XMLByte *) (myxml.c_str()), myxml.size(), "A name");
//    parser->parse(&source);

//    XMLPlatformUtils::Terminate();
	
	//boost::property_tree::xml_parser::read_xml(response_p->content, pt);
//	std::cout << "read property tree";
}

sec::report::report(Url u)
{
	//https_client c(u.host(),u.path_queries());
    //std::string s;
	//s=c.getContent();
	//boost::property_tree::xml_parser::read_xml(s, pt);	
}