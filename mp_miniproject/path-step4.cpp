#include <iostream>
#include <vector>

#include "path_planning.hpp"

int main(int argc, char * argv[]) {
  if ((argc != 5) && argc != 6) {
    std::cerr << "Invalid argument input !" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream graphFile(argv[1]);
  if (!graphFile.is_open()) {
    std::cerr << "Can't open file for graph!" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream obstacleFile(argv[2]);
  if (!obstacleFile.is_open()) {
    std::cerr << "Can't open file for obstacle!" << std::endl;
    return EXIT_FAILURE;
  }

  Graph graph;
  std::vector<unsigned> obstacleNodes;
  parseGraph(graphFile, graph);
  parseObstacle(obstacleFile, obstacleNodes);
  graph.Obstruct(obstacleNodes);

  unsigned startNode;
  unsigned goalNode;
  std::istringstream iss1(argv[3]);
  if (!(iss1 >> startNode)) {
    std::cerr << "Error: Invalid input for the startNode" << std::endl;
    return EXIT_FAILURE;
  }

  std::istringstream iss2(argv[4]);
  if (!(iss2 >> goalNode)) {
    std::cerr << "Error: Invalid input for the goalNode" << std::endl;
    return EXIT_FAILURE;
  }
  // std::cout << graph;
  if (argc == 5) {
    graph.Dijkstra(startNode, goalNode);
  }
  else if (strcmp(argv[5], "-a") == 0) {
    graph.Astar(startNode, goalNode);
  }
  else {
    std::cerr << "Invalid argument input !" << std::endl;
    return EXIT_FAILURE;
  }

  graphFile.close();
  obstacleFile.close();
  return EXIT_SUCCESS;
}
