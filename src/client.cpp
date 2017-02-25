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
	
// Create a context that uses the default paths for
// finding CA certificates.
	ssl::context ctx(ssl::context::sslv23);
	ctx.set_default_verify_paths();
	
	//set up ioservice
	std::shared_ptr<io_service> ioserv(new io_service);
	io_service_p = ioserv;

	//setup ssl stream
	std::shared_ptr<ssl_stream_t> streamp(new ssl_stream_t(*io_service_p,ctx));
	socket_p =  streamp;
	
	ip::tcp::resolver resolver(*io_service);
	ip::tcp::resolver::query query(server, "https");
	boost::asio::connect(socket_p->lowest_layer(), resolver.resolve(query));
	socket_p->lowest_layer().set_option(ip::tcp::no_delay(true));
	// Perform SSL handshake and verify the remote host's
	// certificate.
	socket_p->set_verify_mode(ssl::verify_peer);
	socket_p->set_verify_callback(ssl::rfc2818_verification(server));
	socket_p->handshake(ssl_stream_t::client);
// read and write as normal
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