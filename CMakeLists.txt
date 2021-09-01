cmake_minimum_required(VERSION 3.8)

# set the project name
project(hershensh)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIR include)
set(TEST_DIR tests)

set(HEADER_FILES ${INCLUDE_DIR}/reader.h ${INCLUDE_DIR}/evaluate.h ${INCLUDE_DIR}/printer.h)

# add the executable
add_executable(hershensh hershensh.cpp ${HEADER_FILES})

target_include_directories(hershensh 
  PUBLIC "${INCLUDE_DIR}")

#-------------------------
# Catch2 unittesting framework
find_package(Catch2 REQUIRED)
add_executable(runTests ${TEST_DIR}/test.cpp)
target_include_directories(runTests 
  PRIVATE "${INCLUDE_DIR}")
target_link_libraries(runTests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(runTests)
#-------------------------


