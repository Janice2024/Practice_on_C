#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sortLines(std::istream & input) {
  std::string aLine;
  std::vector<std::string> lines;
  while (!input.eof()) {
    getline(input, aLine);
    lines.push_back(aLine);
  }
  std::sort(lines.begin(), lines.end());
  std::vector<std::string>::iterator it = lines.begin();
  while (it != lines.end()) {
    std::cout << *it << std::endl;
    it++;
  }
  // lines.clear();
}

void sortFile(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    std::ifstream file(argv[i]);
    if (!file.is_open()) {
      std::cerr << "Can't open file!" << std::endl;
      exit(EXIT_FAILURE);
    }
    sortLines(file);
    file.close();
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLines(std::cin);
  }
  else {
    sortFile(argc, argv);
  }
  return EXIT_SUCCESS;
}
