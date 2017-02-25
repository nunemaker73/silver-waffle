#include <iostream>
#include <exception>
#include "sec.h"

int main (int argc, char *argv[])
{
using namespace std;
try {
	
	if (argc != 2) throw "argument usage error";
	sec::sec s(argv[1]);}
}
catch (exception& e)
{
std::cout << e.what();	
}

}
