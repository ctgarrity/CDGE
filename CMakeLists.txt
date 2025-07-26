cmake_minimum_required(VERSION 3.31)
project(CDGE)

set(CMAKE_CXX_STANDARD 23)

add_executable(CDGE src/main.cpp external/volk.h)
