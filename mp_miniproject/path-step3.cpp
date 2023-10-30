#include <iostream>
#include <vector>

#include "path_planning.hpp"

int main(int argc, char * argv[]) {
  if (argc != 5) {
    std::cerr << "Expect exactly three command line argument !" << std::endl;
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
  //   for (std::vector<unsigned>::const_iterator it = obstacleNodes.begin();
  //      it != obstacleNodes.end();
  //      ++it) {
  //   unsigned node = *it;
  //   if (node>graph.)
  //   {
  //     /* code */
  //   }

  // }
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
  graph.Dijkstra(startNode, goalNode);
  graphFile.close();
  obstacleFile.close();
  return EXIT_SUCCESS;
}
