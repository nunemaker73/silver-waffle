#include <iostream>
#include "sec.h"

int main (int argc, char *argv[])
{
	if (argc != 2) // we want a more argument
		std::cout << "Usage : "<< argv[0] << " <stock_symbol>\n";
	else
	{
		std::cout << "Preparing to pull from internet still in main.cpp\n";
		std::cout << argv[1]<<"\n";
		std::cout << "calling the sec-info class now\n";
	  	sec::info s(argv[1]);
		
	}
}
