#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <exception>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>


using boost::asio::ip::tcp;


class client
{
public:
    client(const std::string& server, const std::string& path);
    std::string getContent(){return content_;};
    unsigned int getStatus(){return status_code_;};
    std::string getStatus(){return status_message_;};
    std::string getHeaders(){return headers_;};
    std::string getHttpVersion(){return http_version_;};
	struct connection_error: public exception {
		std::string message_;
		connection_error(std::string message):message_(message){};
		const char * what () const throw() {
			std::string temp("Unable to connect: ");
			temp += message_;
			return temp;}; };
	struct status_error: public exception {
		unsigned int code_
		std::string message_;
		status_error(unsigned int code, std::string message):code_(code),message_(message){};
		const char * what () const throw() {
			std::string temp("Invalid status code: ");
			temp += code_;
			temp += "\n";
			temp += message_;
			return temp;}; };	
	
private:
 //   tcp::resolver resolver_;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
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
    write(std::string data){boost::asio::write(s,boost::asio::buffer(data));};
};

#endif