#include <iostream>

#include <evaluate.hpp>
#include <printer.hpp>
#include <reader.hpp>
#include <tree-sitter-wrapper.hpp>

using namespace hersh;

bool isEOF() {
  return std::cin.eof();
}

int main() {

  TreeSitter ts;

  Reader reader;

  while(true) {
    const auto readLine = reader.read();
    if(isEOF()) {
      std::cout << std::endl;
      break;
    }

    const auto evaluatedLine = evaluate(readLine);
    const auto lineToPrint = print(evaluatedLine);
    std::cout << lineToPrint << "\n";
  };

  return EXIT_SUCCESS;

}
