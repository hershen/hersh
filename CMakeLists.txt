cmake_minimum_required(VERSION 3.8)

# set the project name
project(hersh)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIR include)
set(TEST_DIR tests)

set(HEADER_FILES ${INCLUDE_DIR}/reader.h ${INCLUDE_DIR}/evaluate.h ${INCLUDE_DIR}/printer.h)

# add the executable
add_executable(hersh hersh.cpp ${HEADER_FILES})

target_include_directories(hersh 
  PUBLIC "${INCLUDE_DIR}")
