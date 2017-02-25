#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <exception>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

struct connection_error: public std::exception {
		std::string message_;
		connection_error(std::string message):message_(message){};
		const char * what () const throw() {
			std::string temp("Unable to connect: ");
			temp += message_;
			return temp.data();}; };

struct status_error: public std::exception {
	unsigned int code_;
	std::string message_;
	status_error(unsigned int code, std::string message):code_(code),message_(message){};
	const char * what () const throw() {
		std::string temp("Invalid status code: ");
		temp += code_;
		temp += "\n";
		temp += message_;
		return temp.data();}; };

class https_client
{
public:
    https_client(const std::string& server, const std::string& path);
    std::string getContent(){return content_;};
    unsigned int getStatusCode(){return status_code_;};
    std::string getStatus(){return status_message_;};
    std::string getHeaders(){return headers_;};
    std::string getHttpVersion(){return http_version_;};
		
	
private:
 //   tcp::resolver resolver_;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
    boost::asio::io_service io_service_;
    boost::asio::ssl::context ctx_;
    std::string http_version_;
    unsigned int status_code_;
    std::string status_message_;
    std::string headers_;
    std::string content_;
    std::string readLine();
    std::string readWord();
    unsigned int readInt();
    std::string readHeaders();
    std::string readAll();
    void write(std::string data){boost::asio::write(socket_,boost::asio::buffer(data));};
};

#endif