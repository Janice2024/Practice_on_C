#ifndef __PATH_PLANNING_H__
#define __PATH_PLANNING_H__

#include <math.h>

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <vector>

//This Point class stores info on the id and spacial location of a single node
class Point {
 private:
  unsigned id; //this field indicates the location of the node in a graph vertex vector
  double x;
  double y;

 public:
  Point(unsigned idInfo, double xinfo, double yInfo) : id(idInfo), x(xinfo), y(yInfo) {}
  unsigned getID() { return id; }
  double getX() const { return x; }
  double getY() const { return y; }
  double distanceFrom(const Point & nodeInfo);
  //Given the info of other two nodes, we can calculate the corresponding orientation with "this Point";
  int Orientation(const Point & b, const Point & c) const;  
  friend std::ostream & operator<<(std::ostream & s, const Point & rhs);
};
bool pointComp(Point pointA, Point pointB);

//The Graph class contains two fields: vertex and edge.
class Graph {
 private:
  std::vector<Point> vertex;
  std::vector<std::map<unsigned, double> > edge;

 public:
  void addNode(unsigned idInfo, double xInfo, double yInfo);
  Point getNode(unsigned idInfo);
  //every time we finish reading nodes, we want to create a vertex vector which size is based on the node
  //numer we have;
  void resizeEdge();
  void addEdge(unsigned idA, unsigned idB);

  friend std::ostream & operator<<(std::ostream & s, const Graph & rhs);
  friend double getDist(unsigned idA, unsigned idB, const Graph & rhs);
  void Dijkstra(unsigned startId, unsigned goalId);
  //We use obstruct function to indicate which edges should be removed
  //two path planning algorithms are given below respectively:
  void Obstruct(const std::vector<unsigned> & obstacleNodes);
  void Astar(unsigned startId, unsigned goalId);
};


//We consider path as a sequence of node ids. We calculate the according cost by
//using the node coordinates info from a given graph
class Path {
 private:
  std::vector<unsigned> ids;
  double cost;

 public:
  Path(): cost(0) {}
  std::vector<unsigned> getIds();
  void addNode(unsigned idInfo, const Graph & graph);
  void changeIds(const Path & rhs, const Graph & graph);
  void initializeCost(double costInfo);
  double getCost() const;
  void calculateCost(const Graph & rhs);
  unsigned sumIds();
  friend std::ostream & operator<<(std::ostream & s, const Path & rhs);
};

//Edge consists of two points; given other two points, we can check if this edge intersects with
//our current edge
class Edge {
 private:
  Point a;
  Point b;

 public:
  Edge(const Point & a_, const Point & b_) : a(a_), b(b_) {}
  bool intersect(const Point & c, const Point & d);
  friend std::ostream & operator<<(std::ostream & s, const Edge & rhs);
};
//we use this helper function to check if the x projection and y projection of two edges consisted by 
//these given four nodes will intersect
bool projIntersection(const Point & a, const Point & b, const Point & c, const Point & d);

void parseGraph(std::istream & input, Graph & graph);
void parseNodes(const std::string & line, unsigned & id, double & x, double & y);
void parseEdges(const std::string & line, unsigned & idA, unsigned & idB);
void parseObstacle(std::istream & input, std::vector<unsigned> & obstacleNodes);

#endif
