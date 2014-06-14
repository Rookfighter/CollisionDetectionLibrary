cmake_minimum_required(VERSION 2.6)
project(cdl)

file(GLOB CDL_SRC "src/cdl/*.hpp" "src/cdl/*.cpp")
add_library(cdl ${CDL_SRC})