#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<std::string, std::vector<std::string> > item_t;

item_t * parseLine(const std::string & line);
#endif
