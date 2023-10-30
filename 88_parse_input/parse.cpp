#include "parse.hpp"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>
// any other headers you need

class invalid_input : public std::exception {
  // override what() here

 public:
  // explicit invalid_input(const std::string & message) : message_(message) {}

  // virtual const char * what() const throw() { return message_.c_str(); }
  virtual const char * what() const throw() { return "Invalid input!"; }
  virtual ~invalid_input() throw(){};
};

item_t * parseLine(const std::string & line) {
  std::string key;
  std::vector<std::string> values;

  size_t colon_pos = line.find(":");

  if (colon_pos == std::string::npos) {
    throw invalid_input();
  }
  else {
    key = line.substr(0, colon_pos);
    size_t start = colon_pos + 2;
    for (size_t i = colon_pos + 1; i < line.size(); i++) {
      if (line[i] == ',') {
        values.push_back(line.substr(start, i - start));
        start = i + 2;
      }
    }
    if (start <= line.size()) {
      values.push_back(line.substr(start, line.size() - start));
    }
  }
  item_t * anItemPointer = new item_t(key, values);
  return anItemPointer;
}

itemvc_t parseFile(std::istream & input) {
  itemvc_t itemvc;
  item_t * anItemPointer;
  std::string aLine;
  std::vector<std::string> lines;
  while (!input.eof()) {
    try {
      getline(input, aLine);
      if (aLine.size() > 0) {
        // std::cout << "!" << std::endl;
        anItemPointer = parseLine(aLine);
        itemvc.push_back(anItemPointer);
      }
    }
    catch (invalid_input & in) {
      std::cerr << in.what() << "\n";
    }
  }
  return itemvc;
}

void printFile(itemvc_t itemvc) {
  for (itemvc_t::iterator it = itemvc.begin(); it != itemvc.end(); ++it) {
    item_t * item = *it;
    std::cout << "key = " << item->first << std::endl;
    std::cout << "  values =";
    std::vector<std::string> vector = item->second;
    if (vector.empty()) {
      std::cout << " " << std::endl;
    }
    else {
      for (std::vector<std::string>::size_type i = 0; i < vector.size() - 1; ++i) {
        std::cout << " " << vector[i] << ";";
      }
      std::cout << " " << vector[(vector.size() - 1)] << std::endl;
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Expect exactly one command line argument !" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Can't open file!" << std::endl;
    exit(EXIT_FAILURE);
  }
  itemvc_t itemvc;
  itemvc = parseFile(file);
  // std::cerr << "!!!" << std::endl;
  printFile(itemvc);
  for (itemvc_t::iterator it = itemvc.begin(); it != itemvc.end(); ++it) {
    delete (*it);
  }
  itemvc.clear();
  file.close();
  return EXIT_SUCCESS;
}
