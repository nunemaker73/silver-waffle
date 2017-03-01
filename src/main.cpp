#include <iostream>
#include <xerces/util/PlatformUtils.hpp>

#include "sec.hpp"

int main (int argc, char *argv[])
{
using std::cout;
using std::exception;

try { xerces::XMLPlatformUtils::Initialize()}
catch (const xerces::XMLException& toCatch)
	{std::cout << toCatch.what();}

	sec::sec s(argv[1]);
xerces::XMLPlatformUtils::Terminate();
return 0;
}
