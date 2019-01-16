

#ifndef SERVER_FILECACHEMANAGER_H
#define SERVER_FILECACHEMANAGER_H

#include <string>
#include <cstring>
#include "CacheManager.h"
#include <iostream>
#include <fstream>
#include "Utils.h"

const char fileDelimiter = '$';

using namespace std;

template<typename Problem, typename Solution>
class FileCacheManager : public virtual CacheManager<Problem, Solution> {

private:
    mutex f_mutex;
    map<Problem, Solution> *problemToSolutions;
    vector<string> *vic;
public:

    FileCacheManager() {
        problemToSolutions = new map<Problem, Solution>;
        vic = new vector<string>;
        loadFileToMap();
    }

    bool isSavedInCache(Problem problem) {
        std::lock_guard<mutex> lockGuard(f_mutex);
        return this->problemToSolutions->count(problem) > 0;
    }

    Solution getFromCache(Problem problem) {
        std::lock_guard<mutex> lockGuard(f_mutex);
        return this->problemToSolutions->at(problem);
    }

    void saveSLNForProblem(Problem problem, Solution solution) {
        f_mutex.lock();
        problemToSolutions->insert(make_pair(problem, solution));
        string to_push = problem + fileDelimiter + solution;
        this->vic->push_back(to_push);
        f_mutex.unlock();
    }

    void saveAllToFile() {
        ofstream myfile;
        myfile.open("solution.txt", ios::app | fstream::out);
        for (vector<string>::iterator it = vic->begin(); it != vic->end(); ++it) {
            myfile << *it << "\n";
        }
        myfile.close();
    }

    void loadFileToMap() {
        ifstream myfile;
        string line;
        vector<string> parsing;
        myfile.open("solution.txt");
        while (getline(myfile, line)) {
            parsing = Utils::splitToVectorByDelimiter(line, fileDelimiter);
            problemToSolutions->insert(make_pair(parsing.at(0), parsing.at(1)));
        }
        myfile.close();

    }

    ~FileCacheManager() {
        saveAllToFile();
        delete vic;
        delete problemToSolutions;
    }
};


#endif //SERVER_FILECACHEMANAGER_H
