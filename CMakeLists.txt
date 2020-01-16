cmake_minimum_required(VERSION 3.15)
project(02_approvvigionamento)

set(CMAKE_CXX_STANDARD 14)

add_executable(02_approvvigionamento main.cpp Model.cpp Model.h Component.cpp Component.h Entity.cpp Entity.h)