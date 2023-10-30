#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include "task.hpp"

TaskDep::TaskDep(const task_t & t) : task(t) {
}
const task_t & TaskDep::getTask() const {
  return task;
}
void TaskDep::addPredecessor(const task_t & t) {
  pres.push_back(t);
}
std::list<task_t> TaskDep::getPredecessors() const {
  return pres;
}

TaskDep * parseLine(const std::string & line) {
  std::string key;
  std::vector<std::string> values;

  size_t colon_pos = line.find(":");

  if (colon_pos == std::string::npos) {
    std::cerr << "Wrong format" << std::endl;
    exit(EXIT_FAILURE);
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
  TaskDep * anItemPointer = new TaskDep(key);
  for (size_t i = 0; i < values.size(); i++) {
    (*anItemPointer).addPredecessor(values[i]);
  }
  return anItemPointer;
}

TaskDeps_t parseFile(std::istream & input) {
  TaskDeps_t TaskDeps;
  TaskDep * anItemPointer;
  std::string aLine;
  std::vector<std::string> lines;
  while (!input.eof()) {
    getline(input, aLine);
    if (aLine.size() > 0) {
      // std::cout << "!" << std::endl;
      anItemPointer = parseLine(aLine);
      TaskDeps.push_back(anItemPointer);
    }
  }
  return TaskDeps;
}
bool removable(std::list<task_t> & ans, TaskDeps_t & TaskDeps, int & i) {
  bool removeOnce = true;
  int maxDist = 0;  //the index for the first position to insert the task if possible
  std::list<task_t> currentPres = (*TaskDeps[i]).getPredecessors();
  task_t currenTask = (*TaskDeps[i]).getTask();
  if (currentPres.empty()) {
    ans.push_front(currenTask);
    delete TaskDeps[i];
    TaskDeps.erase(TaskDeps.begin() + i);
    i = i - 1;
    return removeOnce;
  }

  for (std::list<task_t>::iterator it = currentPres.begin(); it != currentPres.end();
       ++it) {
    std::list<task_t>::iterator p = std::find(ans.begin(), ans.end(), (*it));
    if (p == ans.end()) {
      removeOnce = false;
      return removeOnce;
    }
    int dist = std::distance(ans.begin(), p);
    if (dist > maxDist) {
      maxDist = dist;
    }
  }
  //insert
  std::list<task_t>::iterator it = ans.begin();
  std::advance(it, maxDist + 1);
  ans.insert(it, currenTask);

  //remove
  delete TaskDeps[i];
  TaskDeps.erase(TaskDeps.begin() + i);
  return removeOnce;
}

int main(int argc, char ** argv) {
  // open file for reading
  if (argc != 2) {
    std::cerr << "Expect exactly one command line argument !" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Can't open file!" << std::endl;
    exit(EXIT_FAILURE);
  }
  // make dependency list of tasks from input file
  TaskDeps_t TaskDeps = parseFile(file);
  size_t goalAnsSize = TaskDeps.size();
  // order list according to dependencies

  std::list<task_t> ans;
  bool removeAny = true;
  bool removeOnce = false;
  while (removeAny) {
    removeAny = false;
    for (int i = 0; i < (int)TaskDeps.size(); ++i) {
      removeOnce = removable(ans, TaskDeps, i);
      removeAny = (removeAny || removeOnce);
    }
  }

  if (ans.size() != goalAnsSize) {
    for (TaskDeps_t::iterator it = TaskDeps.begin(); it != TaskDeps.end(); ++it) {
      delete (*it);
    }
    TaskDeps.clear();
    file.close();
    std::cerr << "Can't create a to-do list!" << std::endl;
    return EXIT_FAILURE;
  }

  // print todo list

  std::list<std::string>::iterator it = ans.begin();
  std::cout << *it;
  ++it;
  while (it != ans.end()) {
    std::cout << ", " << *it;
    ++it;
  }
  std::cout << std::endl;

  //  std::cout << (*TaskDeps[3]).pres << std::endl;

  for (TaskDeps_t::iterator it = TaskDeps.begin(); it != TaskDeps.end(); ++it) {
    delete (*it);
  }
  TaskDeps.clear();
  file.close();
  return EXIT_SUCCESS;
}
