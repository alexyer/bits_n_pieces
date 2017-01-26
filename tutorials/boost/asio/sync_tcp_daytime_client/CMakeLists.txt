project(sync_tcp_daytime_client)

find_package(Boost 1.63.0 REQUIRED system date_time)

set(CMAKE_CXX_FLAGS "-lboost_system")
set(CMAKE_CXX_FLAGS_DEBUG  ${CMAKE_CXX_FLAGS})

set(SOURCE_FILES main.cpp)

add_executable(sync_tcp_daytime_client ${SOURCE_FILES})