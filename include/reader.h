#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

namespace hershensh {

std::string read(const std::string& prompt) {
  std::string line;

  std::cout << prompt << " ";

  std::getline(std::cin, line);
  return line;
}
}

