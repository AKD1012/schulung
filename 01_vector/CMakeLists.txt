cmake_minimum_required(VERSION 3.0.0)
project(ex_vector VERSION 0.1.0)

add_executable(ex_vector ex_vector.cpp generate_randomstring.cpp)
set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
