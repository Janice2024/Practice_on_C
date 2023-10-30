#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point c_init, double r_init) : center(c_init), radius(r_init) {}
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
