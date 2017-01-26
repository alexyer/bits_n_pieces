#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main() {
    boost::asio::io_service io;

    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

    t.async_wait([](const boost::system::error_code& code){ std::cout << "Hello, World!" << std::endl; });

    io.run();
    return 0;
}