cmake_minimum_required(VERSION 3.8)
project(OnionLayer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp OnionLayer.cpp OnionLayer.h)
add_executable(OnionLayer ${SOURCE_FILES})