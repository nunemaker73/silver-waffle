#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
#include "client.hpp"
using boost::asio::ip::tcp;

client::client(const std::string& server, const std::string& path)
{

    
    boost::asio::io_service io_service;
	boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
	boost::asio::ssl::stream<asio:ip::tcp::socket> s(io_service, ctx);
	
	std::string data;
	
	
	//	Establish a connection to the server
	s.connect(host,"https");
	if (!s) throw connection_error(s.error().message(});
	
	s.handshake(client);
	
	data =  "GET "+ path +" HTTP/1.0\r\nHost: " + path + "r\nConnection: close\r\n\r\n";
	write(data);
	http_version_ = readWord();
	status_code_ = readWord();
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
	read_until(s,b,"\r\n");
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	return line;
}

std::string readHeaders()
{
	using boost::asio;
	streambuf b;
	read_until(s,b,"\r\n\r\n");
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
	read_until(s,b,' ');
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	return line;
}

unsigned int readWord()
{
	using boost::asio;
	streambuf b;
	read_until(s,b,' ');
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
	read(s, b);
	std::istream is(&b);
	std::string data;
	std::getline(is,data);
	return data;
}

/*
int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cout << "Usage: https_client <server> <path>\n";

            return 1;
        }

        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        ctx.set_default_verify_paths();

        boost::asio::io_service io_service;
        client c(io_service, ctx, argv[1], argv[2]);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}
*/