#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
#include "client.hpp"


client::client(const std::string& server, const std::string& path):
ctx_(boost::asio::ssl::context::sslv23),
socket_(io_service_,ctx_)
{
	std::string data;
	
	
	//	Establish a connection to the server
	//socket_.connect(host,"https");
	//if (!socket_) throw connection_error(socket_.error().message(});
	
	socket_.handshake(client);
	
	data =  "GET "+ path +" HTTP/1.0\r\nHost: " + path + "r\nConnection: close\r\n\r\n";
	write(data);
	http_version_ = readWord();
	status_code_ = readInt();
	status_message_=readLine();
	std::cout << "http_version: " << http_version_ << "\n";
	if (http_version_.substr(0,5) != "HTTP/") throw "Invalid response\n";
	if (status_code_ !=200) throw status_error(status_code_,readLine();
	headers_ = readHeaders();
	content_ = readAll()
}
std::string readLine()
{
	using boost::asio;
	streambuf b;
	read_until(socket_,b,"\r\n");
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	return line;
}

std::string readHeaders()
{
	using boost::asio;
	streambuf b;
	read_until(socket_,b,"\r\n\r\n");
	std::istream is(&b);
	std::string data="";
	for (std::string line; std::getline(is,line) ){
		data+=line;}
	return data;
}

std::string readWord()
{
	using boost::asio;
	streambuf b;
	read_until(socket_,b,' ');
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	return line;
}

unsigned int readWord()
{
	using boost::asio;
	streambuf b;
	read_until(socket_,b,' ');
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	unsigned int ret = std::stoi(line);
	return ret;
}

std::string readAll()
{
	using boost::asio;
	streambuf b;
	read(socket_, b);
	std::istream is(&b);
	std::string data;
	std::getline(is,data);
	return data;
}