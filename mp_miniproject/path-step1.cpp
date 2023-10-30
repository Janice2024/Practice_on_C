#include "path_planning.hpp"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Expect exactly one command line argument !" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Can't open file!" << std::endl;
    return EXIT_FAILURE;
  }
  Graph graph;
  parseGraph(file, graph);

  std::cout << graph;

  file.close();
  return EXIT_SUCCESS;
}
