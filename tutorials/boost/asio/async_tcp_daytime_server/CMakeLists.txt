project(async_tcp_daytime_server)

find_package(Boost 1.58.0 REQUIRED system date_time)

set(CMAKE_CXX_FLAGS "-lboost_system")
set(CMAKE_CXX_FLAGS_DEBUG  ${CMAKE_CXX_FLAGS})

set(SOURCE_FILES main.cpp)

add_executable(async_tcp_daytime_server ${SOURCE_FILES})