#include "path_planning.hpp"

//step1
//Here to parse a graph, we first read the file line by line;
//if we encounter "$nodes" section, we will use parseNodes() function to deal with it;
//if we encounter "$edges" section, we will use parseEdges() function to deal with it;
double Point::distanceFrom(const Point & nodeInfo) {
  double dist = sqrt(pow(x - nodeInfo.x, 2) + pow(y - nodeInfo.y, 2));
  return dist;
}

// Print out each single node
std::ostream & operator<<(std::ostream & s, const Point & rhs) {
  s << "(";
  s << rhs.x;
  s << ",";
  s << rhs.y;
  s << ")";
  return s;
}

bool pointComp(Point pointA, Point pointB) {
  return (pointA).getID() < (pointB).getID();
}

void Graph::addNode(unsigned idInfo, double xInfo, double yInfo) {
  vertex.push_back(Point(idInfo, xInfo, yInfo));
  std::sort(vertex.begin(), vertex.end(), pointComp);  //faster algorithm?
}

Point Graph::getNode(unsigned idInfo) {
  for (size_t i = 0; i < vertex.size(); i++) {
    if (vertex[i].getID() == idInfo) {
      return vertex[i];
    }
  }
  std::cerr << "There is no such a node!" << std::endl;
  exit(EXIT_FAILURE);
}

//create the edge vector based on the number of vertex
void Graph::resizeEdge() {
  edge.resize(vertex.size());
}

void Graph::addEdge(unsigned idA, unsigned idB) {
  Point pointA = getNode(idA);
  Point pointB = getNode(idB);
  double weight = (pointA).distanceFrom(pointB);
  edge[idA].insert(std::make_pair(idB, weight));
  edge[idB].insert(std::make_pair(idA, weight));
}

//Print out a graph
std::ostream & operator<<(std::ostream & s, const Graph & rhs) {
  for (size_t i = 0; i < rhs.vertex.size(); i++) {
    s << (rhs.vertex[i]);
    s << " ";
  }
  s << std::endl;
  for (size_t i = 0; i < rhs.edge.size(); i++) {
    s << i << ": ";
    std::map<unsigned, double>::const_iterator it;  //why it has to be const_interator?
    for (it = rhs.edge[i].begin(); it != rhs.edge[i].end(); ++it) {
      std::cout << it->first << "," << it->second << " ";
    }
    s << std::endl;
  }

  return s;
}

void parseEdges(const std::string & line, unsigned & idA, unsigned & idB) {
  //check the number of spaces !!!
  int spaceNum = 0;
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] == ' ') {
      spaceNum++;
    }
  }

  if (spaceNum != 1) {
    std::cerr << "Wrong format" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::size_t space = line.find(' ');
  if (space == std::string::npos) {
    std::cerr << "Wrong format! " << '\n';
    exit(EXIT_FAILURE);
  }
  std::string strA = line.substr(0, space);
  std::string strB = line.substr(space, line.size() - space);
  char * endptr;
  idA = strtod(strA.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << strA.c_str() << '\n';
    exit(EXIT_FAILURE);
  }
  idB = strtod(strB.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << strB.c_str() << '\n';
    exit(EXIT_FAILURE);
  }
}

void parseNodes(const std::string & line, unsigned & id, double & x, double & y) {
  //check the number of spaces !!!
  int spaceNum = 0;
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] == ' ') {
      spaceNum++;
    }
  }

  if (spaceNum != 2) {
    std::cerr << "Wrong format" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::size_t firstSpace = line.find(' ');
  std::size_t secondSpace = line.find(' ', firstSpace + 1);
  if (firstSpace == std::string::npos || secondSpace == std::string::npos) {
    std::cerr << "Wrong format! " << '\n';
    exit(EXIT_FAILURE);
  }
  std::string strid = line.substr(0, firstSpace);
  std::string strx = line.substr(firstSpace, secondSpace - firstSpace);
  std::string stry = line.substr(secondSpace, line.size() - secondSpace);

  char * endptr;
  id = strtod(strid.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << strid.c_str() << '\n';
    exit(EXIT_FAILURE);
  }
  x = strtod(strx.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << strx.c_str() << '\n';
    exit(EXIT_FAILURE);
  }
  y = strtod(stry.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << stry.c_str() << '\n';
    exit(EXIT_FAILURE);
  }
}

void parseGraph(std::istream & input, Graph & graph) {
  unsigned id;
  double x;
  double y;
  unsigned idA;
  unsigned idB;
  std::string aLine;
  std::vector<std::string> lines;
  bool readNodes = false;
  bool readEdges = false;
  while (!input.eof()) {
    getline(input, aLine);
    if (aLine.size() > 0) {
      if (aLine == "$nodes") {
        readNodes = true;
        continue;
      }
      if (aLine == "$edges") {
        if (readNodes != true) {
          std::cerr << "Put in node info first! " << '\n';
          exit(EXIT_FAILURE);
        }
        readNodes = false;
        readEdges = true;
        continue;
      }
      if (readNodes == true) {
        parseNodes(aLine, id, x, y);
        // std::cout << "id: " << id << "x: " << x << "y: " << y << "\n";
        graph.addNode(id, x, y);
      }

      if (readEdges == true) {
        parseEdges(aLine, idA, idB);
        // std::cout << "idA: " << idA << "idB: " << idB;
        graph.resizeEdge();
        graph.addEdge(idA, idB);
      }
    }
  }
}

//step2
void Path::addNode(unsigned idInfo, const Graph & graph) {
  ids.push_back(idInfo);
  calculateCost(graph);
}
//get distance between any given two nodes
double getDist(unsigned idA, unsigned idB, const Graph & rhs) {
  std::map<unsigned, double>::const_iterator it = rhs.edge[idA].find(idB);
  if (it != rhs.edge[idA].end()) {
    return it->second;
  }
  else {
    std::cout << "Edge not found" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Path::initializeCost(double costInfo) {
  cost = costInfo;
}

double Path::getCost() const {
  return cost;
}

//calculate cost for this path in a given graph
void Path::calculateCost(const Graph & rhs) {
  cost = 0;
  for (size_t i = 0; i < ids.size() - 1; i++) {
    cost += getDist(ids[i], ids[i + 1], rhs);
  }
}

//print out a path
std::ostream & operator<<(std::ostream & s, const Path & rhs) {
  for (size_t i = 0; i < rhs.ids.size(); i++) {
    s << rhs.ids[i] << " ";
  }
  s << ": ";
  s << rhs.cost;
  return s;
}

std::vector<unsigned> Path::getIds() {
  return ids;
}

void Path::changeIds(const Path & rhs, const Graph & graph) {
  ids = rhs.ids;
  calculateCost(graph);
}

unsigned Path::sumIds() {
  double sum = 0;
  for (size_t i = 0; i < ids.size(); i++) {
    sum += ids[i];
  }
  return sum;
};

class NodeInfo {
 public:
  unsigned id;
  double cost;

  NodeInfo(unsigned id_, double cost_) : id(id_), cost(cost_) {}

  bool operator<(const NodeInfo & rhs) const { return cost > rhs.cost; }
};

// Dijkstra algorithm
void Graph::Dijkstra(unsigned startId, unsigned goalId) {
  if (std::max(startId, goalId) >= vertex.size()) {
    std::cerr << "Invalid input!" << std::endl;
    exit(EXIT_FAILURE);
  }

  double posInf = std::numeric_limits<double>::infinity();
  std::set<unsigned> completed;
  std::priority_queue<NodeInfo> unvisited;
  unsigned currentId = startId;

  std::vector<Path> paths(vertex.size(),Path());
  paths[0].addNode(startId, *this);
  paths[0].initializeCost(0);  //the cost to go from the start point to itself is 0
  for (size_t i = 1; i < vertex.size(); i++) {
    paths[i].addNode(startId, *this);
    paths[i].initializeCost(posInf);
  }
  unvisited.push(NodeInfo(startId, paths[startId].getCost()));

  while (!unvisited.empty()) {
    std::set<unsigned> unvisitedNeighbor;
    std::map<unsigned, double>::iterator it;  //key-value pair in a map
    for (it = edge[currentId].begin(); it != edge[currentId].end(); ++it) {
      std::set<unsigned>::iterator idIt = completed.find(it->first);
      if (idIt == completed.end()) {  //for those unvisited neighbor
        if ((paths[currentId].getCost() + it->second) < paths[it->first].getCost()) {
          paths[it->first].changeIds(paths[currentId], *this);
          paths[it->first].addNode(it->first, *this);
          unvisited.push(NodeInfo(it->first, paths[it->first].getCost()));
          std::cout << paths[it->first] << std::endl;
        }
        else if ((paths[currentId].getCost() + it->second) ==
                 paths[it->first].getCost()) {
          //if two paths have the same cost, choose the one with the lower id sum
          if ((paths[currentId].sumIds() + it->first) < paths[it->first].sumIds()) {
            paths[it->first].changeIds(paths[currentId], *this);
            paths[it->first].addNode(it->first, *this);
            unvisited.push(NodeInfo(it->first, paths[it->first].getCost()));
            std::cout << paths[it->first] << std::endl;
          }
        }
      }
    }
    completed.insert(currentId);
    unvisited.pop();
    currentId = unvisited.top().id;
  }
  if (paths[goalId].getCost() < posInf) {
    std::cout << "Best path: " << paths[goalId] << std::endl;
  }
  else {
    std::cout << "Path not found" << std::endl;
    exit(EXIT_FAILURE);
  }
}

//step3
//Here we add parseObstacle() function to read obstacles from a file;
//we also have member function obstruct() in graph class to remove edges being obstructed;
int Point::Orientation(const Point & b, const Point & c) const {
  int ot;
  ot = (b.getY() - y) * (c.getX() - b.getX()) - (b.getX() - x) * (c.getY() - b.getY());
  if (ot != 0) {  //when ot = 0, collinear
    if (ot > 0) {
      ot = 1;  //clockwise
    }
    else {
      ot = -1;  //counterclockwise
    }
  }
  return ot;
}

bool projIntersection(const Point & a,
                      const Point & b,
                      const Point & c,
                      const Point & d) {
  bool xInter = false;
  bool yInter = false;
  bool projInter = false;
  if (std::max(a.getX(), b.getX()) > std::min(c.getX(), d.getX()) &&
      std::max(c.getX(), d.getX()) > std::min(a.getX(), b.getX())) {
    xInter = true;
  }
  if (std::max(a.getY(), b.getY()) > std::min(c.getY(), d.getY()) &&
      std::max(c.getY(), d.getY()) > std::min(a.getY(), b.getY())) {
    yInter = true;
  }
  if (xInter && yInter) {
    projInter = true;
  }

  return projInter;
}

bool Edge::intersect(const Point & c, const Point & d) {
  bool inter = false;
  int ot1 = a.Orientation(b, c);
  int ot2 = a.Orientation(b, d);
  int ot3 = c.Orientation(d, a);
  int ot4 = c.Orientation(d, b);
  //Two line segments a-b and c-d intersect
  if ((ot1 != ot2) && (ot3 != ot4)) {
    inter = true;
  }
  // or collinear in the special case
  if ((ot1 == 0) && (ot2 == 0) && (ot3 == 0) && (ot4 == 0) &&
      projIntersection(a, b, c, d)) {
    inter = true;
  }

  return inter;
}

std::ostream & operator<<(std::ostream & s, const Edge & rhs) {
  s << "{" << rhs.a << ", " << rhs.b << "}";
  return s;
}
void Graph::Obstruct(const std::vector<unsigned> & obstacleNodes) {
  std::map<unsigned, double> emptyMap;
  //broken cases
  if (obstacleNodes.size() == 1) {
    std::cerr << "Invalid obstacle!" << std::endl;
    exit(EXIT_FAILURE);
  }
  //construct an edge for each pair of obstacleNodes
  std::vector<Edge> obstacleEdges;
  for (size_t i = 0; i < obstacleNodes.size(); ++i) {
    //erase edge of graph for nodes adjacent to an obstacleNode
    edge[obstacleNodes[i]] = emptyMap;
    for (size_t j = i + 1; j < obstacleNodes.size(); ++j) {
      obstacleEdges.push_back(Edge(getNode(obstacleNodes[i]), getNode(obstacleNodes[j])));
    }
  }

  // std::cout << "!" << std::endl;
  //iterate over all edges in the graph
  for (size_t i = 0; i < edge.size(); i++) {
    for (std::map<unsigned, double>::iterator it = edge[i].begin();
         it != edge[i].end();) {
      bool removable = false;

      //for all obstacleEdges
      for (size_t j = 0; j < obstacleEdges.size(); j++) {
        // std::cout << "!" << std::endl;
        if (obstacleEdges[j].intersect(getNode(i), getNode(it->first))) {
          removable = true;
        }
      }
      // std::cout << "?" << std::endl;
      if (removable) {
        // std::cout << "(" << i << "," << it->first << ")" << std::endl;
        edge[it->first].erase(i);
        edge[i].erase(it++);  //?
      }
      else {
        ++it;
      }
    }
  }
}

void parseObstacle(std::istream & input, std::vector<unsigned> & obstacleNodes) {
  bool readObstacles = false;
  std::string aLine;
  while (!input.eof()) {
    getline(input, aLine);
    if (aLine.size() > 0) {
      if (aLine == "$obstacles") {
        readObstacles = true;
        continue;
      }
      if (readObstacles) {
        std::istringstream iss3(aLine);
        unsigned nodeId;

        while (iss3 >> nodeId) {
          obstacleNodes.push_back(nodeId);
        }
      }
    }
  }
}

//step4
// Here we change Dijkstra algorithm by selecting the next node to move by comparing
//the sum of the nodes' distance from the start node and its Eucledean distance to the
//goal node
void Graph::Astar(unsigned startId, unsigned goalId) {
  if (std::max(startId, goalId) >= vertex.size()) {
    std::cerr << "Invalid input!" << std::endl;
    exit(EXIT_FAILURE);
  }

  double posInf = std::numeric_limits<double>::infinity();
  std::set<unsigned> completed;
  std::priority_queue<NodeInfo> unvisited;
  unsigned currentId = startId;

  std::vector<Path> paths(vertex.size());
  paths[0].addNode(startId, *this);
  paths[0].initializeCost(0);  //the cost to go from the start point to itself is 0
  for (size_t i = 1; i < vertex.size(); i++) {
    paths[i].addNode(startId, *this);
    paths[i].initializeCost(posInf);
  }
  unvisited.push(NodeInfo(
      startId,
      (paths[startId].getCost() + getNode(startId).distanceFrom(getNode(goalId)))));

  while (!unvisited.empty()) {
    std::set<unsigned> unvisitedNeighbor;
    std::map<unsigned, double>::iterator it;  //key-value pair in a map
    for (it = edge[currentId].begin(); it != edge[currentId].end(); ++it) {
      std::set<unsigned>::iterator idIt = completed.find(it->first);
      if (idIt == completed.end()) {  //for those unvisited neighbor
        if ((paths[currentId].getCost() + it->second) < paths[it->first].getCost()) {
          paths[it->first].changeIds(paths[currentId], *this);
          paths[it->first].addNode(it->first, *this);
          unvisited.push(NodeInfo(it->first,
                                  paths[it->first].getCost() +
                                      getNode(it->first).distanceFrom(getNode(goalId))));
          std::cout << paths[it->first] << std::endl;
          if (it->first == goalId) {
            std::cout << "Best path: " << paths[goalId] << std::endl;
            exit(EXIT_SUCCESS);
          }
        }

      }
    }
    completed.insert(currentId);
    unvisited.pop();
    currentId = unvisited.top().id;
  }

    std::cout << "Path not found" << std::endl;
    exit(EXIT_FAILURE);

}
