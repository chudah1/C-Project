cmake_minimum_required(VERSION 3.23)
project(C-Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(C-Project main.cpp Airport.cpp FlightNode.cpp Route.cpp BFS.cpp)
