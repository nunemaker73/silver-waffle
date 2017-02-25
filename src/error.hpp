#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>

struct basic_error: public std::exception {
		std::string message_;
		basic_error(std::string message):message_(message){};
		const char * what () const throw() {
			return message_.data()+"\n";} };
#endif