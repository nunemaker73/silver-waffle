#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <memory> //shared_ptr
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>


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
 	using boost::asio::ssl::stream;
 	using boost::asio::ip::tcp::socket;
    using boost::asio::io_service;
    //using boost::asio::ssl:context;
    std::shared_ptr<stream<socket>> socket_p;
    std::shared_ptr<io_service> io_service_p;
    //std::shared_ptr<context> ctx_p;
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
    void write(std::string data){boost::asio::write(*socket_p,boost::asio::buffer(data));};
};

#endif