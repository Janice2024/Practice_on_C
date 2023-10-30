#include "euler.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

odesoln_t EulerSimulation::operator()(const std::vector<double> & tspan,
                                      const std::vector<double> & ics,
                                      size_t n) {
  std::vector<double> t(n);
  std::vector<std::vector<double> > states(n, std::vector<double>(ics.size()));

  //the time vector being divided into pieces with length delta_t
  t[0] = tspan[0];
  double delta_t = (tspan[1] - tspan[0]) / (double)(n - 1);

  //initialize the state variables
  for (size_t k = 0; k < ics.size(); k++) {
    states[0][k] = ics[k];
  }
  //calculate the state variables at each time point based on euler
  for (size_t i = 1; i < n; i++) {
    t[i] = t[i - 1] + delta_t;
    for (size_t j = 0; j < ics.size(); j++) {
      states[i][j] =
          states[i - 1][j] + delta_t * (ode->operator()(t[i - 1], states[i - 1]))[j];
    }
  }

  // odesoln_t ans(t, states);
  odesoln_t ans = std::make_pair(t, states);
  return ans;
}

std::ostream & operator<<(std::ostream & s, const odesoln_t & rhs) {
  for (size_t i = 0; i < rhs.first.size(); i++)  //the number of time points in rhs
  {
    s << rhs.first[i] << ",";
    s << rhs.second[i][0] << ",";
    s << rhs.second[i][1] << "\n";
  }
  return s;
}
