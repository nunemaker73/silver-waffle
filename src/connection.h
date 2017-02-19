#ifndef SEC_CONNECTION_H
#define SEC_CONNECTION_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "url.hpp"
namespace sec {
//connection class will connect and get stream ready for content parse
class connection{
private:
	boost::property_tree::ptree pt;
	int connect(Url u);
public:
	connection(std::string stock_name);
	connection(Url u);
	std::string getFact(std::string key){pt.get<std::string>(key);};
};
}
#endif