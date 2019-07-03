cmake_minimum_required(VERSION 3.13)
project(TCPClient)

set(CMAKE_CXX_STANDARD 11)



add_executable(TCPClient main.cpp RawTransport.h RawTransport.cpp Client.cpp Client.h)

target_link_libraries(TCPClient -pthread -lboost_thread -lboost_system)