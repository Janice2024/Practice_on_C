#include "point.hpp"

#include <cmath>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
}
