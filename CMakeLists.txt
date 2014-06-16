cmake_minimum_required(VERSION 2.6)
project(cdl)

file(GLOB CDL_SRC "src/cdl/*.hpp" "src/cdl/*.cpp")
include_directories(include)
add_library(cdl ${CDL_SRC} ${CDL_INCLUDE})

include_directories("../../UnitTest++/src")
get_filename_component(UNIT_TEST_LIB_DIR "../../UnitTest++/build" ABSOLUTE) 
link_directories(${UNIT_TEST_LIB_DIR})
file(GLOB CDL_TEST_SRC "test/*.cpp")
add_executable(cdlTest ${CDL_TEST_SRC})
target_link_libraries(cdlTest cdl "UnitTest++")
