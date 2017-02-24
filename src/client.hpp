#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;

class client
{
public:
    client(boost::asio::io_service& io_service,
           boost::asio::ssl::context& context,
           const std::string& server, const std::string& path);
    std::string getContent();

private:

    void handle_resolve(const boost::system::error_code& err,
                        tcp::resolver::iterator endpoint_iterator);
    bool verify_certificate(bool preverified,
                            boost::asio::ssl::verify_context& ctx);
    void handle_connect(const boost::system::error_code& err);
    void handle_handshake(const boost::system::error_code& error);
    void handle_write_request(const boost::system::error_code& err);
    
    void handle_read_status_line(const boost::system::error_code& err);
    void handle_read_headers(const boost::system::error_code& err);
    void handle_read_content(const boost::system::error_code& err);

    tcp::resolver resolver_;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
    boost::asio::streambuf request_;
    boost::asio::streambuf status_;
    boost::asio::streambuf headers_;
    boost::asio::streambuf content_;
};

#endif