#include "yyy.hpp"

#include <exception>
// any other headers you need

class invalid_input : public std::exception {
  // override what() here
  std::string mes;

 public:
  invalid_input(const char * message) : mes(message) {}

  virtual const char * what() const noexcept { return mes.c_str(); }
};

item_t * parseLine(const std::string & line) {
  std::string key;
  std::vector<std::string> values;

  size_t colonN = line.find(":");
  if (colonN == std::string::npos) {
    throw invalid_input("Missing colon");
  }
  key = line.substr(0, colonN);

  if (colonN != line.length() - 1) {
    std::string dec;
    dec = line.substr(colonN + 2);
    std::stringstream sstring(dec);
    std::string value;
    while (std::getline(sstring, value, ',')) {
      values.push_back(value);
    }
  }

  item_t * ans = new item_t(key, values);
  return ans;
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input) {
    std::cerr << "Could not open file " << argv[1] << std::endl;
    return 1;
  }

  std::vector<item_t *> items;
  std::string line;
  while (std::getline(input, line)) {
    try {
      item_t * item = parseLine(line);
      items.push_back(item);
    }
    catch (const invalid_input & e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }

  for (auto item : items) {
    std::cout << "key = " << item->first << std::endl;
    std::cout << "  values = ";
    if (item->second.empty()) {
      std::cout << "" << std::endl;
    }
    else {
      for (size_t i = 0; i < item->second.size(); ++i) {
        std::cout << item->second[i];
        if (i != item->second.size() - 1) {
          std::cout << "; ";
        }
        else {
          std::cout << std::endl;
        }
      }
    }
  }

  for (auto item : items) {
    delete item;
  }
  return 0;
}
