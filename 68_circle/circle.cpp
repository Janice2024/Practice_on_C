#include "circle.hpp"

#include <cmath>

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  double ans;

  if (d > radius + otherCircle.radius) {
    ans = 0;
  }

  else if (d <= (radius - otherCircle.radius) && radius >= otherCircle.radius)
    ans = M_PI * pow(otherCircle.radius, 2);

  else if (d <= (otherCircle.radius - radius) && otherCircle.radius >= radius)
    ans = M_PI * pow(radius, 2);
  else {
    ans =
        radius * radius *
            std::acos(
                (d * d + radius * radius - otherCircle.radius * otherCircle.radius) /
                (2 * d * radius)) +
        otherCircle.radius * otherCircle.radius *
            acos((d * d + otherCircle.radius * otherCircle.radius - radius * radius) /
                 (2 * d * otherCircle.radius)) -
        0.5 *
            sqrt((-d + radius + otherCircle.radius) * (d + radius - otherCircle.radius) *
                 (d - radius + otherCircle.radius) * (d + radius + otherCircle.radius));
  }
  return ans;
}
