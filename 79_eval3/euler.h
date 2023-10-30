#ifndef __EULER__H__
#define __EULER__H__
#include <cstdlib>
#include <iostream>
#include <vector>

#include "myode.h"

typedef std::pair<std::vector<double>, std::vector<std::vector<double> > > odesoln_t;

class EulerSimulation {
 private:
  MyOde * ode;

 public:
  EulerSimulation(const MyOde & newOde) : ode(new MyOde(newOde)){};
  ~EulerSimulation() { delete ode; };
  odesoln_t operator()(const std::vector<double> & tspan,
                       const std::vector<double> & ics,
                       size_t n);
  friend void testEuler(EulerSimulation & es);
};

std::ostream & operator<<(std::ostream & s, const odesoln_t & rhs);

#endif
