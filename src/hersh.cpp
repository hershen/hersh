#include <iostream>

#include <src/evaluate.hpp>
#include <src/printer.hpp>
#include <src/reader.hpp>

using namespace hersh;

const std::string defaultPrompt = "hersh";

bool isEOF() {
  return std::cin.eof();
}

int main(int argc, char *argv[]) {

  while(true) {
    const auto readLine = read(defaultPrompt);
    if(isEOF()) {
      std::cout << std::endl;
      break;
    }

    const auto evaluatedLine = eval(readLine);
    print(evaluatedLine);
  };

  return EXIT_SUCCESS;

}
