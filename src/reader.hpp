#pragma once

#include <cstdlib>

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

namespace hersh {

class Reader {
public:
  explicit Reader() : 
    Reader(std::cin, std::cout)
    {}

  explicit Reader(std::istream& istream, std::ostream& ostream) : 
    istream(istream.rdbuf()),
    ostream(ostream.rdbuf())
    {}

  std::string read() const {
    std::string line;

    ostream << prompt;

    std::getline(istream, line);
    return line;
  }

  void setPrompt(const std::string& aPrompt) {
    prompt = aPrompt;
  }

  std::string getPrompt() const {
    return prompt;
  }

private:
  mutable std::istream istream;
  mutable std::ostream ostream;
  std::string prompt = "hersh$ ";
};

} // namepace hersh

