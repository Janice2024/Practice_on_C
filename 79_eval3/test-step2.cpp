#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

#include "euler.h"

int main() {
  double p[] = {1, 0.1, 5, 2, 6};
  MyOde anOde(std::vector<double>(p, p + 5));
  EulerSimulation euler(anOde);
  std::vector<double> tspan(2);
  tspan[0] = 0;
  tspan[1] = 1;
  std::vector<double> ics(2);
  ics[0] = 0;
  ics[1] = 0.1;
  size_t n = 3;
  odesoln_t timeStatePair = euler.operator()(tspan, ics, n);
  std::cout << timeStatePair;
}
