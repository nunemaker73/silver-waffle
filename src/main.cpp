#include <iostream>
#include <exception>
#include "sec.h"

int main (int argc, char *argv[])
{
	if (argc != 2) // we want a more argument
		std::cout << "Usage : "<< argv[0] << " <stock_symbol>\n";
	else
	{
		try{ sec::sec s(argv[1]);}
	  	catch (std::exception& e){std::cout << e.what();};
		
	}
}
