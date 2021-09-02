# hersh

## Introduction
This project aims to build a shell named `hersh`.
The goal is for the shell to be fully compliant to [The Open Group Base Specifications, Issue 7, 2018 Edition](https://publications.opengroup.org/standards/unix/c181) which is identical to IEEE Std 1003.1, 2017 Edition.

## Building
### Requirements
* C++ compiler supporting C++17.
* [CMake](https://github.com/Kitware/CMake) version 3.8+.

### Compiling

Run the commands:

```bash
mkdir build
cd build
cmake ..
make
```

This will create the `hersh` binary inside the `build` directory.

## Usage
Run the `hersh` binary located in the `build` directory to open the hersh shell.

## Test suite

There are two ways to run the test suite:

1. `make test` will run the tests through `CMake`'s ctest driver program.
2. Run the `runTests` binary, located in the `tests` directory. The `runTests` binary is created by the `Catch2` framework.
