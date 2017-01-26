#include <array>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        boost::asio::io_service io;

        tcp::resolver resolver(io);
        tcp::resolver::query query(argv[1], "daytime");

        auto endpoint_iterator = resolver.resolve(query);

        tcp::socket socket(io);
        boost::asio::connect(socket, endpoint_iterator);

        for (;;) {
            std::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}