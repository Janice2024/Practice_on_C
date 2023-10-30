#ifndef __MY_ODE__H__
#define __MY_ODE__H__
#include <cstdlib>
#include <iostream>
#include <vector>

class MyOde {
 private:
  double m;
  double c;
  double k;
  double a;
  double om;

 public:
  MyOde(const std::vector<double> & paras) :
      m(paras[0]), c(paras[1]), k(paras[2]), a(paras[3]), om(paras[4]) {}

  std::vector<double> operator()(double t, const std::vector<double> & state);

  unsigned getOrder();

  friend std::ostream & operator<<(std::ostream & s, const MyOde & rhs);
};

// std::ostream & operator<<(std::ostream & s, const MyOde & rhs);

#endif
