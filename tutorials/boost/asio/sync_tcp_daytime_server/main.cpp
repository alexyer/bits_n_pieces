#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
    using namespace std;
    auto now = time(0);
    return ctime(&now);
}

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
    typedef std::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_service &service) {
        return pointer(new tcp_connection(service));
    }


    tcp::socket &socket() {
        return socket_;
    }

    void start() {
        message_ = make_daytime_string();
        boost::asio::async_write(socket_, boost::asio::buffer(message_),
                                 boost::bind(&tcp_connection::handle_write, shared_from_this()));
    }

private:
    tcp_connection(boost::asio::io_service &io_service) : socket_(io_service) {}

    void handle_write() {}

    tcp::socket socket_;
    std::string message_;
};

class tcp_server {
public:
    tcp_server(boost::asio::io_service &io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 13)) {
        std::cout << "Listen on: " << acceptor_.local_endpoint().address().to_string() << ":" << acceptor_.local_endpoint().port() << std::endl;
        start_accept();
    }

    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error) {
        if (!error) {
            new_connection->start();
        }

        start_accept();
    }
private:
    void start_accept() {
        tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());

        acceptor_.async_accept(new_connection->socket(), boost::bind(&tcp_server::handle_accept, this, new_connection,
                                                                     boost::asio::placeholders::error));
    }

    tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_service io_service;
        tcp_server server(io_service);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}