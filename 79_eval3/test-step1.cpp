#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

#include "myode.h"

int main() {
  double p[] = {1, 0.1, 5, 2, 6};
  MyOde ode(std::vector<double>(p, p + 5));
  std::cout << ode;
  // std::cout << ode.getOrder() << "\n";
  std::vector<double> v(2);
  v[0] = 0.5;
  v[1] = 0;
  std::vector<double> q = ode(0.0, v);
  std::cout << "{";
  std::cout << q[0];
  std::cout << ",";
  std::cout << q[1];
  std::cout << "}";
}
