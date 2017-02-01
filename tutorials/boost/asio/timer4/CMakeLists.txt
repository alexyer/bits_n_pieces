project(timer4)

find_package(Boost 1.58.0 REQUIRED system date_time)

set(CMAKE_CXX_FLAGS "-lboost_system")
set(CMAKE_CXX_FLAGS_DEBUG  ${CMAKE_CXX_FLAGS})

set(SOURCE_FILES main.cpp)

add_executable(timer4 ${SOURCE_FILES})