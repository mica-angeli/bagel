#include <iostream>
#include <argparse/argparse.hpp>

int main(int argc, char *argv[]) {
  argparse::ArgumentParser parser("bagel");

  try {
    parser.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << parser;
    std::exit(1);
  }

    std::cout << "Hello World!" << std::endl;
    return 0;
}
