#include <iostream>
#include "simulator.h"
#include "arg_parser.h"

int main(int argc, char* argv[]) {
  try {
    std::string input = ArgParser::Parse(argc, argv);
    if (input.empty()) return 0;

    Simulator sim(input);
    sim.Run();

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}