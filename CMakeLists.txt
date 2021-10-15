cmake_minimum_required(VERSION 3.8)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.16") 
  cmake_policy(SET CMP0097 NEW) #Don't download git submodules if GIT_SUBMODULES is empty
endif()

project(hersh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(EXTERNAL_DIR ${PROJECT_SOURCE_DIR}/external)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Output compile commands to file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic -O3)

include(ExternalProject)

#-------------------------
# tree-sitter
message(CHECK_START "Configuring tree-sitter")

ExternalProject_Add(tree-sitter
  GIT_REPOSITORY https://github.com/tree-sitter/tree-sitter
  GIT_SHALLOW    True
  GIT_TAG        v0.20.0
  GIT_PROGRESS   True
  
  PREFIX ${EXTERNAL_DIR}/tree-sitter
  CONFIGURE_COMMAND ""
  BUILD_IN_SOURCE   True #Because we're running tree-sitter's Makefile, which is in the source directory.
  INSTALL_COMMAND   ""
)

ExternalProject_Get_Property(tree-sitter source_dir)
set(tree-sitter_SOURCE_DIR ${source_dir})
set(tree-sitter_INCLUDE_DIR ${tree-sitter_SOURCE_DIR}/lib/include)

message(CHECK_START "Finished configuring tree-sitter")
#-------------------------

#-------------------------
# tree-sitter-bash
message(CHECK_START "Configuring tree-sitter-bash")

ExternalProject_Add(tree-sitter-bash
  GIT_REPOSITORY https://github.com/tree-sitter/tree-sitter-bash
  GIT_TAG        v0.19.0
  GIT_SHALLOW    True
  GIT_SUBMODULES "" #Prevent download of bash-it, used for testing in tree-sitter-bash
  GIT_PROGRESS   True

  PREFIX ${EXTERNAL_DIR}/tree-sitter-bash

  DEPENDS tree-sitter

  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
)

ExternalProject_Get_Property(tree-sitter-bash source_dir)
set(tree-sitter-bash_SOURCE_DIR ${source_dir})
ExternalProject_Get_Property(tree-sitter-bash binary_dir)
set(tree-sitter-bash_BINARY_DIR ${binary_dir})

message(CHECK_START "Finished configuring tree-sitter-bash")
#-------------------------

#Compile tree-sitter-bash parser.c and scanner.cc into object files
add_custom_command(
  OUTPUT ${tree-sitter-bash_BINARY_DIR}/parser.o ${tree-sitter-bash_BINARY_DIR}/scanner.o
  COMMAND ${CMAKE_C_COMPILER} -c -O3 -I${tree-sitter_INCLUDE_DIR} ${tree-sitter-bash_SOURCE_DIR}/src/parser.c -o ${tree-sitter-bash_BINARY_DIR}/parser.o
  COMMAND ${CMAKE_CXX_COMPILER} -c -O3 -I${tree-sitter_INCLUDE_DIR} ${tree-sitter-bash_SOURCE_DIR}/src/scanner.cc -o ${tree-sitter-bash_BINARY_DIR}/scanner.o
  DEPENDS ${tree-sitter-bash_SOURCE_DIR}/src/parser.c ${tree-sitter-bash_SOURCE_DIR}/src/scanner.cc
  )
add_library(libtree-sitter-bash OBJECT IMPORTED)
set_target_properties(libtree-sitter-bash
                      PROPERTIES IMPORTED_OBJECTS "${tree-sitter-bash_BINARY_DIR}/parser.o;${tree-sitter-bash_BINARY_DIR}/scanner.o"
)

set(HEADER_FILES ${SOURCE_DIR}/reader.hpp ${SOURCE_DIR}/evaluate.hpp ${SOURCE_DIR}/printer.hpp)

add_executable(hersh ${SOURCE_DIR}/hersh.cpp
  ${HEADER_FILES}
  )

target_include_directories(hersh 
  PRIVATE ${SOURCE_DIR}
          ${tree-sitter_INCLUDE_DIR}
)
target_link_libraries(hersh
  PRIVATE ${tree-sitter_SOURCE_DIR}/libtree-sitter.a
          libtree-sitter-bash
)

add_dependencies(hersh tree-sitter tree-sitter-bash libtree-sitter-bash)

#-------------------------
# Catch2 unittesting framework
message(CHECK_START "Configuring Catch2")

Include(FetchContent)
set(FETCHCONTENT_QUIET off)


set(FETCHCONTENT_BASE_DIR ${EXTERNAL_DIR}/Catch2)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git

  # Catch2 devel branch for 2021-09-02. v3.0.0-preview3 has a bug where './runTests --list-tests --verbosity quiet' shows additional lines which are (wrongly) interpreted as tests.
  GIT_TAG        432d03d1aab8472a0813c34a7f0e2e1a2c585d22 

  GIT_PROGRESS   True

)

FetchContent_MakeAvailable(Catch2)

set(TESTS 
  ${SOURCE_DIR}/evaluate.test.cpp
  ${SOURCE_DIR}/printer.test.cpp
  ${SOURCE_DIR}/reader.test.cpp 
)

add_executable(runTests ${TESTS})
target_include_directories(runTests 
  PRIVATE ${SOURCE_DIR})
target_link_libraries(runTests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras) # Because we use FetchContent
include(CTest)
include(Catch)
catch_discover_tests(runTests)
#-------------------------

set(FETCHCONTENT_BASE_DIR ${EXTERNAL_DIR})
