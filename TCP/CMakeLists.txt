cmake_minimum_required(VERSION 3.13)
project(TCP)

set(CMAKE_C_STANDARD 11)

add_executable(TCP main.c wrapper.cpp wrapper.h Server.h Server.cpp)

target_link_libraries(TCP -lpthread -lboost_thread)