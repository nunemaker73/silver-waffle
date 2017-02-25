#include <iostream>
#include "error.hpp"
#include "sec.h"

int main (int argc, char *argv[])
{
using std::cout;
using std::exception;
try {
	
	if (argc != 2) throw basic_error("argument usage error");

	sec::sec s(argv[1]);
}
catch (exception& e)
{
	cout << e.what()<<"\n";	
}
return 0;
}
