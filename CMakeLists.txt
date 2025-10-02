cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


project(Orderbook)

add_executable(Orderbook main.cpp
    src/Order.cpp
    src/Orderbook.cpp
)