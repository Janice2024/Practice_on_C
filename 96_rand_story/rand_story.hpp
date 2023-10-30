#ifndef __RAND_STORY__
#define __RAND_STORY__

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>

class Story{
    private:

    std::map<std::string, std::vector<std::string> > wordList;

    public:

void readWordList(const std::string &filename) {
    std::ifstream file(filename.c_str());
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string category, word;
        std::getline(iss, category, ':');
        // while (std::getline(iss, word, ':')) {
        //     wordList[category].push_back(word);
        }
    }

}



#endif
