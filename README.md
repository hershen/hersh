# hershensh

## Introduction
This project aims to build a shell named `hershensh`.
The goal is for the shell to be fully compliant to [The Open Group Base Specifications, Issue 7, 2018 Edition](https://publications.opengroup.org/standards/unix/c181) which is identical to IEEE Std 1003.1, 2017 Edition.

## Building
### Requirements
* C++ compiler supporting C++17.
* [CMake](https://github.com/Kitware/CMake) version 3.8+.

For running the test suite:
* [Catch2](https://github.com/catchorg/Catch2) unit testing framework.

### Compiling

Run the commands:

```bash
mkdir build
cd build
cmake ..
make
```

This will create the `hershensh` binary.

## Usage
From the `build` directory run `./hershensh` which will run the hershensh shell.

## Test suite

From the `build` directory run `./runTests`.
