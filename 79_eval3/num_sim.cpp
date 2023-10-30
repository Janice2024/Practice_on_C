#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

#include "euler.h"

int main(int argc, char * argv[]) {
  if (argc != 5) {
    std::cerr << "Error: Expected four command line arguments" << std::endl;
    return EXIT_FAILURE;
  }

  //parse parameters to the ODE
  std::string odePars = argv[1];
  double m;
  double c;
  double k;
  double a;
  double om;
  //to ensure tha four commas are contained
  int commaNum = 0;
  for (size_t i = 0; i < odePars.size(); i++) {
    if (odePars[i] == ',') {
      commaNum++;
    }
  }

  if (commaNum != 4) {
    std::cerr << "Error: Expected 4 commas" << std::endl;
    return EXIT_FAILURE;
  }

  //now we divide the odePars into 5 pieces
  std::string dividedPars[5];
  size_t start = 0;
  size_t j = 0;  //the jth params we are parsing
  for (size_t i = 0; i < odePars.size(); i++) {
    if (odePars[i] == ',') {
      // if (i - start == 0) {
      //   std::cout << "Error: incompleted ODE parameters" << std::endl;
      //   return EXIT_FAILURE;
      // }
      dividedPars[j] = odePars.substr(start, i - start);
      start = i + 1;
      ++j;
    }
  }
  //check if om, the last ode paras, is missing
  // if (start == (odePars.size())) {
  //   std::cout << "Error: lacking om" << std::endl;
  //   return EXIT_FAILURE;
  // }
  dividedPars[4] = odePars.substr(start, odePars.size() - start);

  //convert these ode paras from str to double
  char * endptr;
  m = strtod(dividedPars[0].c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << dividedPars[0] << '\n';
    return EXIT_FAILURE;
  }
  c = strtod(dividedPars[1].c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << dividedPars[1] << '\n';
    return EXIT_FAILURE;
  }
  k = strtod(dividedPars[2].c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << dividedPars[2] << '\n';
    return EXIT_FAILURE;
  }
  a = strtod(dividedPars[3].c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << dividedPars[3] << '\n';
    return EXIT_FAILURE;
  }
  om = strtod(dividedPars[4].c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << dividedPars[4] << '\n';
    return EXIT_FAILURE;
  }

  std::vector<double> paras;
  paras.push_back(m);
  paras.push_back(c);
  paras.push_back(k);
  paras.push_back(a);
  paras.push_back(om);

  //parsing the time span
  std::string tspan_str = argv[2];
  double ti;
  double tf;
  //to see if there is a comma
  std::size_t pos = tspan_str.find(",");
  if (pos == std::string::npos) {
    std::cerr << "Delimiter not found\n";
    return EXIT_FAILURE;
  }
  std::string ti_str = tspan_str.substr(0, pos);
  std::string tf_str = tspan_str.substr(pos + 1);

  ti = strtod(ti_str.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << ti_str << '\n';
    return EXIT_FAILURE;
  }
  tf = strtod(tf_str.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << tf_str << '\n';
    return EXIT_FAILURE;
  }

  std::vector<double> tspan;
  tspan.push_back(ti);
  tspan.push_back(tf);

  //parsing the initial conditions
  std::string ics_str = argv[3];
  double x0;
  double v0;
  //to see if there is a comma
  pos = ics_str.find(",");
  if (pos == std::string::npos) {
    std::cerr << "Delimiter not found\n";
    return EXIT_FAILURE;
  }
  std::string x0_str = ics_str.substr(0, pos);
  std::string v0_str = ics_str.substr(pos + 1);

  x0 = strtod(x0_str.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << x0_str << '\n';
    return EXIT_FAILURE;
  }
  v0 = strtod(v0_str.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cerr << "Invalid input: " << v0_str << '\n';
    return EXIT_FAILURE;
  }

  std::vector<double> ics;
  ics.push_back(x0);
  ics.push_back(v0);

  //parsing the number of points
  size_t n;
  std::istringstream iss(argv[4]);
  iss >> n;
  if (!iss.eof() || iss.fail()) {
    std::cerr << "Invalid input: " << argv[4] << '\n';
    return EXIT_FAILURE;
  }

  MyOde anOde(paras);
  EulerSimulation euler(anOde);
  odesoln_t timeStatePair = euler.operator()(tspan, ics, n);
  std::cout << timeStatePair;
  return 0;
}
