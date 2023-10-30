#include "myode.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

std::vector<double> MyOde::operator()(double t, const std::vector<double> & state) {
  std::vector<double> ans(2);
  ans[0] = state[1];
  ans[1] = (a * sin(om * t) - c * state[1] - k * state[0]) / m;
  return ans;
}

unsigned MyOde::getOrder() {
  unsigned order;
  if (m != 0) {
    order = 2;
  }
  else if (c != 0) {
    order = 1;
  }
  else {
    order = 0;
  }
  return order;
}

std::ostream & operator<<(std::ostream & s, const MyOde & ode) {
  if (ode.m != 0) {
    s << ode.m;
    s << "*";
    s << "xddot ";
    s << "+ ";
  }
  if (ode.c != 0) {
    s << ode.c;
    s << "*";
    s << "xdot ";
    s << "+ ";
  }
  if (ode.k != 0) {
    s << ode.k;
    s << "*";
    s << "x ";
  }
  s << "= ";
  if (ode.a != 0) {
    s << ode.a;
    s << "*";
    s << "sin(";
    s << ode.om;
    s << "*t)";
  }
  else {
    s << "0";
  }
  return s;
}
