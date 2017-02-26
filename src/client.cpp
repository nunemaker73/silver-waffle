#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
//#include <boost/system.hpp>
#include "error.hpp"
#include "client.hpp"


https_client::https_client(const std::string& server, const std::string& path)
{
	using namespace boost::asio;
	std::string data;
	std::vector<std::string> lines;
	
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
	
	ip::tcp::resolver resolver(*io_service_p);
	ip::tcp::resolver::query query(server, "https");
	boost::asio::connect(socket_p->lowest_layer(), resolver.resolve(query));
	socket_p->lowest_layer().set_option(ip::tcp::no_delay(true));
	// Perform SSL handshake and verify the remote host's
	// certificate.
	socket_p->set_verify_mode(ssl::verify_peer);
	socket_p->set_verify_callback(ssl::rfc2818_verification(server));
	socket_p->handshake(ssl_stream_t::client);
// read and write as normal
	std::cout << "path: "<<path << "\n";
	data =  "GET "+ path +" HTTP/1.0\r\nHost: " + server+"\r\nConnection: close\r\n\r\n";
	write(data);
	std::cout << "getting response:\n";
	{
		streambuf b;
		read(*socket_p, b);
		std::istream is(&b);
		for(int i=0;is;i++) {std::getline(is,lines[i]);}
	}
	
	std::cout << "Finished readlines\n";
	
	http_version_=lines[0].substr(0,lines[0].find_first_of(" "));
	status_code_ = std::stoi(lines[0].substr(lines[0].find_first_of(" ")+1));
	std::cout<< "HTTP version: " << http_version_ <<"\n";
	std::cout<<"Status Code: " << status_code_ << "\n";
	int i=1;
	for (i=1; lines[i]!="\r\n";i++) 
		{headers_=headers_+lines[i];}
	std::cout << "Headers read next lines\n" << headers_;
	i++;
	for (i; i<lines.size();i++) 
		{content_=content_+lines[i];}
	
	
}