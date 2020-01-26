cmake_minimum_required(VERSION 3.15)
project(02_approvvigionamento)

set(CMAKE_CXX_STANDARD 14)

add_executable(02_approvvigionamento main.cpp Model.cpp Model.h Component.cpp Component.h ComponentUsage.cpp ComponentUsage.h Part.cpp Part.h Order.h Order.cpp Warehouse.cpp Warehouse.h Supply.cpp Supply.h parsers/FileParser.cpp parsers/FileParser.h parsers/ComponentParser.cpp parsers/ComponentParser.h parsers/ModelParser.cpp parsers/ModelParser.h parsers/ModelListParser.cpp parsers/ModelListParser.h parsers/OrderParser.cpp parsers/OrderParser.h BatchProcessor.cpp BatchProcessor.h BatchPeriod.cpp BatchPeriod.h Supply.cpp Supply.h)