#include <iostream>

#include "evaluate.h"
#include "printer.h"
#include "reader.h"

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
