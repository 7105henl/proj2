#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <string>
#include <vector>
#include "bits/stdc++.h"
#include "State.h"
#include "SearcherResult.h"
#include "Point.h"
#include <fstream>


using namespace std;

class Utils {

public:
    static vector<string> splitToVectorByDelimiter(string str, char delimiter);

    static string parser(string toReverse);

    static Point getPointFromString(string str);

    static vector<vector<int>> vecStrToMat(vector<string> vector1);

    static vector<std::string> split(const string& s, char delimiter);

    static string delimiterAndIndex(string str, char delimiter, int index);

    template<typename T>
    static SearcherResult getSearcherResult(State<T> state, int numOfEvaluatedNodes) {
        vector<string> shortestPath;
        State<T> *ptr = state.getPrevious();
        shortestPath.push_back(state.getDetails());
        int dist = 0;
        int cost = state.getCost();
        while (ptr != NULL) {
            ++dist;
            cost += ptr->getCost();
            shortestPath.push_back(ptr->getDetails());
            ptr = ptr->getPrevious();
        }
        string parsedPath = parsingVectorOfPointsToPath(shortestPath);
        SearcherResult res;

        res.path = parsedPath;
        res.distance = dist;
        res.cost = cost;
//        cout<<"THIS IS THE COST: "<<endl;
//        cout<<res.cost<<endl;
        res.numOfEvaluatedNodes = numOfEvaluatedNodes;

        return res;
    }

    static string parsingVectorOfPointsToPath(vector<string> vic) {
        string calculation;
        int p1_x, p1_y;
        int p2_x, p2_y;
        // instead of reverse the vector, iteration starts from the end.
        for (vector<string>::iterator it = vic.end(); it > vic.begin() + 1;) {
            it--;
            p1_x = stoi(delimiterAndIndex(*it, ',', 1));
            p1_y = stoi(delimiterAndIndex(*it, ',', 2));
            p2_x = stoi(delimiterAndIndex(*(it - 1), ',', 1));
            p2_y = stoi(delimiterAndIndex(*(it - 1), ',', 2));
            if (p2_x > p1_x) {
                calculation += "DOWN,";
            } else if (p2_x < p1_x) {
                calculation += "UP,";
            } else if (p2_y > p1_y) {
                calculation += "RIGHT,";
            } else {
                calculation += "LEFT,";
            }
        }
        string finalResult = calculation.substr(0, calculation.size() - 1);
//        writeToFile(finalResult);
        return finalResult;
    }

    static void writeToFile(string data) {
            ofstream outfile;
            outfile.open("./solution.txt", ios_base::app);
            outfile << data+"\n";
            outfile.close();
    }
};


#endif //SERVER_UTILS_H
