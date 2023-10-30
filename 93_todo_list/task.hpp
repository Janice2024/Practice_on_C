#include <list>
#include <string>
#include <vector>

typedef std::string task_t;

class TaskDep {
 private:
  const task_t task;
  std::list<task_t> pres;

 public:
  // write these
  TaskDep(const task_t & t);
  const task_t & getTask() const;
  void addPredecessor(const task_t & t);
  std::list<task_t> getPredecessors() const;
};

typedef std::vector<TaskDep *> TaskDeps_t;

// a toy example
// std::list<int> a;
// a.push_back(1);
// a.push_back(2);
// a.push_back(3);

// std::list<int>::iterator p = std::find(a.begin(), a.end(), 2);
// std::list<int>::iterator q = std::find(a.begin(), a.end(), 3);
// int dist1 = std::distance(a.begin(), p);
// int dist2 = std::distance(a.begin(), q);
// bool is = dist1 > dist2;
// std::cout << is << std::endl;
