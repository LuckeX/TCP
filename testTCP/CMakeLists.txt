cmake_minimum_required(VERSION 3.13)
project(testTCP)

set(CMAKE_CXX_STANDARD 14)

add_executable(testTCP main.cpp RawTransport.h RawTransport.cpp Server.cpp Server.h)

target_link_libraries(testTCP -lpthread -lboost_thread -lboost_system)