#include <iostream>
#include <sstream>
#include <vector>

#include "path_planning.hpp"

int main(int argc, char * argv[]) {
  if (argc != 4) {
    std::cerr << "Expect exactly three command line argument !" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Can't open file!" << std::endl;
    return EXIT_FAILURE;
  }
  unsigned startNode;
  unsigned goalNode;
  std::istringstream iss1(argv[2]);
  if (!(iss1 >> startNode)) {
    std::cerr << "Error: Invalid input for the startNode" << std::endl;
    return EXIT_FAILURE;
  }

  std::istringstream iss2(argv[3]);
  if (!(iss2 >> goalNode)) {
    std::cerr << "Error: Invalid input for the goalNode" << std::endl;
    return EXIT_FAILURE;
  }

  Graph graph;
  parseGraph(file, graph);
  // std::cout << graph;
  graph.Dijkstra(startNode, goalNode);
  file.close();
  return EXIT_SUCCESS;
}
