cmake_minimum_required(VERSION 3.8)

project(hersh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR src)
set(EXTERNAL_DIR ${PROJECT_SOURCE_DIR}/external)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


set(HEADER_FILES ${SOURCE_DIR}/reader.hpp ${SOURCE_DIR}/evaluate.hpp ${SOURCE_DIR}/printer.hpp)

add_executable(hersh ${SOURCE_DIR}/hersh.cpp ${HEADER_FILES})

target_include_directories(hersh 
  PRIVATE "${PROJECT_SOURCE_DIR}")

#-------------------------
# Catch2 unittesting framework
message(CHECK_START "Configuring Catch2")

Include(FetchContent)
set(FETCHCONTENT_QUIET off)


set(FETCHCONTENT_BASE_DIR ${EXTERNAL_DIR}/Catch2)
FetchContent_Declare(
  Catch2
  GIT_SHALLOW    TRUE
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git

  # Catch2 main branch. It's better if this is some tag, but the latest v3.0.0-preview3 has a bug where './runTests --list-tests --verbosity quiet' shows additional lines which are (wrongly) interpreted as tests.
  GIT_TAG        devel 
)

FetchContent_MakeAvailable(Catch2)

add_executable(runTests ${SOURCE_DIR}/hersh.test.cpp)
target_include_directories(runTests 
  PRIVATE "${SOURCE_DIR}")
target_link_libraries(runTests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras) # Because we use FetchContent
include(CTest)
include(Catch)
catch_discover_tests(runTests)
#-------------------------

set(FETCHCONTENT_BASE_DIR ${EXTERNAL_DIR})
