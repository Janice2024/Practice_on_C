#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
double Vector2D::getMagnitude() const {
  return std::sqrt(x * x + y * y);
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D sum;
  sum.x = x + rhs.x;
  sum.y = y + rhs.y;
  return sum;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  double prod;
  prod = x * rhs.x + y * rhs.y;
  return prod;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
