cmake_minimum_required(VERSION 3.6)
project(bits_n_pieces)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(tutorials/boost/asio/timer1)
add_subdirectory(tutorials/boost/asio/timer2)
add_subdirectory(tutorials/boost/asio/timer3)
add_subdirectory(tutorials/boost/asio/timer4)
add_subdirectory(tutorials/boost/asio/sync_tcp_daytime_client)
add_subdirectory(tutorials/boost/asio/async_tcp_daytime_server)
add_subdirectory(tutorials/boost/asio/sync_udp_daytime_client)
add_subdirectory(tutorials/boost/asio/async_udp_daytime_server)