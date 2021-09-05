#include <iostream>

#include <hersh/evaluate.hpp>
#include <hersh/printer.hpp>
#include <hersh/reader.hpp>

using namespace hersh;

const std::string defaultPrompt = "hersh$ ";

bool isEOF() {
  return std::cin.eof();
}

int main(int argc, char *argv[]) {
  Reader reader;
  reader.setPrompt(defaultPrompt);

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
