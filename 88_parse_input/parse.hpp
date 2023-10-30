#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include <string>
#include <utility>
#include <vector>

typedef std::pair<std::string, std::vector<std::string> > item_t;
typedef std::vector<item_t *> itemvc_t;

item_t * parseLine(const std::string & line);
itemvc_t parseFile(std::istream & input);
void printFile(itemvc_t itemvc);

#endif
