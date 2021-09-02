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
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_SHALLOW    TRUE
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git

  # Catch2 main branch as of 2021-09-02. It's better if this is some tag, but the latest v3.0.0-preview3 has a bug where './runTests --list-tests --verbosity quiet' shows additional lines which are (wrongly) interpreted as tests.
  GIT_TAG        9ac9fb164e5b20ad9e2f59556b75b9e6f1600f68 
)

FetchContent_MakeAvailable(Catch2)

add_executable(runTests ${TEST_DIR}/test.cpp)
target_include_directories(runTests 
  PRIVATE "${INCLUDE_DIR}")
target_link_libraries(runTests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras) # Because we use FetchContent
include(CTest)
include(Catch)
catch_discover_tests(runTests)
#-------------------------


