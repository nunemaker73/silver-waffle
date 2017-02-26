#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/system.hpp>
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
	std::cout << "readlines next:\n";
	std::vector<std::string> lines;
	do{
		lines[i] = readLine();
		if lines[i] =="EOF"
		{
			lines.pop_back();
			break;
		}
	}

	std::cout << "Finished readlines\n";
	
	http_version_=lines[0].substr(0,lines[0].find_first_of(" "));
	status_code << lines[0].substr(lines[0].find_first_of(" ")+1);
	int i=1;
	do {
		headers_=headers+lines[i];
		i++;
	} until (lines[i]=="\r\n");
	std::cout << "Headers read next lines\n" << headers_;
	
}
std::string https_client::readLine()
{
	using namespace boost::asio;
	streambuf b;
	try{
	read_until(*socket_p,b,"\n");
	}
	catch (boost::system::error& e)
	{
		if (e.what()=="End of File") 
			return "EOF";
		else throw e;
	}
	
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	std::cout << line << "\n";
	return line;
}

std::string https_client::readHeaders()
{
	using namespace boost::asio;
	streambuf b;
	std::cout << "preparing to read headers";
	read_until(*socket_p,b,"\r\n\r\n");
	std::istream is(&b);
	std::string data;
	is >> data;
	std::cout << data << "\n";
	return data;
}

std::string https_client::readWord()
{
	
	return line;
}

unsigned int https_client::readInt()
{
	using namespace boost::asio;
	streambuf b;
	read_until(*socket_p,b,"\n");
	std::istream is(&b);
	std::string line;
	std::getline(is,line);
	
	std::cout << line << "\readInt\n";
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
	is >> data;
	//std::getline(is,data);
	
	std::cout << data<< "\n";
	return data;
}