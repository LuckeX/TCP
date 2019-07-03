cmake_minimum_required(VERSION 3.13)
project(GObject_Signal)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/include/glib-2.0 /usr/lib/x86_64-linux-gnu/glib-2.0/include)

add_executable(GObject_Signal main.c signal-demo.c signal-demo.h)

target_link_libraries(GObject_Signal -lgobject-2.0 -lglib-2.0)