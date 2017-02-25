#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
#include "error.hpp"
#include "client.hpp"


https_client::https_client(const std::string& server, const std::string& path)
{
	using namespace boost::asio;
	std::string data;
	
	ssl::context ctx(ssl::context::sslv23);
	
	std::shared_ptr<io_service> ioserv(new io_service);
	io_service_p = ioserv;
	
	std::shared_ptr<ssl_stream_t> streamp;
	streamp=new ssl_stream_t(*io_service,ctx);
	socket_p =  streamp;
	     
	//	Establish a connection to the server
	//socket_.connect(host,"https");
	//if (!socket_) throw connection_error(socket_.error().message(})
	socket_p->handshake (ssl::stream<ip::tcp::socket>::client);

	data =  "GET "+ path +" HTTP/1.0\r\nHost: " + path + "r\nConnection: close\r\n\r\n";
	write(data);
	http_version_ = readWord();
	status_code_ = readInt();
	status_message_=readLine();
	std::cout << "http_version: " << http_version_ << "\n";
	if (http_version_.substr(0,5) != "HTTP/") throw "Invalid response\n";
	if (status_code_ !=200) throw status_error(status_code_,readLine());
	headers_ = readHeaders();
	content_ = readAll();
}
std::string https_client::readLine()
{
	using namespace boost::asio;
	streambuf b;
	read_until(*socket_p,b,"\r\n");
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	return line;
}

std::string https_client::readHeaders()
{
	using namespace boost::asio;
	streambuf b;
	read_until(*socket_p,b,"\r\n\r\n");
	std::istream is(&b);
	std::string data="";
	for (std::string line; std::getline(is,line); ){
		data+=line;}
	return data;
}

std::string https_client::readWord()
{
	using namespace boost::asio;
	streambuf b;
	read_until(*socket_p,b,' ');
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	return line;
}

unsigned int https_client::readInt()
{
	using namespace boost::asio;
	streambuf b;
	read_until(*socket_p,b,' ');
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	unsigned int ret = std::stoi(line);
	return ret;
}

std::string https_client::readAll()
{
	using namespace boost::asio;
	streambuf b;
	read(*socket_p, b);
	std::istream is(&b);
	std::string data;
	std::getline(is,data);
	return data;
}