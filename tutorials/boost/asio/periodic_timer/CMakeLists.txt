project(periodic_timer)

find_package(Boost 1.58.0 REQUIRED system date_time)

set(CMAKE_CXX_FLAGS "-lboost_system")
set(CMAKE_CXX_FLAGS_DEBUG  ${CMAKE_CXX_FLAGS})

set(SOURCE_FILES main.cpp)

add_definitions(-DBOOST_LOG_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(periodic_timer ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})