#pragma once

#include <cstdlib>

#include <iostream>
#include <istream>
#include <string>

namespace hersh {

class Reader {
public:
  explicit Reader() : 
    istream(std::cin),
    ostream(std::cout)
    {}

  explicit Reader(std::istream& istream, std::ostream& ostream) : 
    istream(istream),
    ostream(ostream)
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
  std::istream& istream;
  std::ostream& ostream;
  std::string prompt = "hersh$ ";
};

} // namepace hersh

