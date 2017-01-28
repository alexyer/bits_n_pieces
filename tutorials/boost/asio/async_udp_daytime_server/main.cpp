#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string() {
    using namespace std;
    auto now = time(0);
    return ctime(&now);
}

class udp_server {
public:
    udp_server(boost::asio::io_service &io_service) : socket_(io_service, udp::endpoint(udp::v4(), 13)) {
        std::cout << "Listen on: " << socket_.local_endpoint().address().to_string() << ":"
                  << socket_.local_endpoint().port() << std::endl;
        start_receive();
    }

private:
    void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred) {
        if (!error || error == boost::asio::error::message_size) {
            auto message = std::make_shared<std::string>(make_daytime_string());
            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                                  boost::bind(&udp_server::handle_send, this, message, boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
            start_receive();
        }
    }

    void handle_send(const std::shared_ptr<std::string> message, const boost::system::error_code &error,
                     std::size_t bytes_transferred) {};

    void start_receive() {
        socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,
                                   boost::bind(&udp_server::handle_receive, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
    }


    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1> recv_buffer_;
};

int main() {
    try {
        boost::asio::io_service io_service;
        udp_server server(io_service);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}