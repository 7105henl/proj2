#ifndef SERVER_MYCLIENTHANDLER_H
#define SERVER_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "Utils.h"
#include <string>
#include "Searcher.h"
#include "SearchableMatrix.h"
#include "Dfs.h"
#include "BestFs.h"
#include "Bfs.h"
#include "Tester.h"
#include "Astar.h"
#include <numeric>

template<typename Solution, typename Problem>
class MyClientHandler : public ClientHandler {

private:
    Solver<Solution, Problem> *solver;
    CacheManager<string, string> *cacheManager;
public:
    MyClientHandler(Solver<Solution, Problem> *solver1, CacheManager<string, string> *cacheManager1) {
        this->solver = solver1;
        this->cacheManager = cacheManager1;
    }

    string handleClient(vector<string> vic) {
        // Parsing vector to matrix
        string data = "";
        string start_p = vic.at(vic.size() - 2);
        string end_p = vic.at(vic.size() - 1);
        Point start = Utils::getPointFromString(start_p);
        Point end = Utils::getPointFromString(end_p);
        vector<string> vic2(vic.begin(), vic.end() - 2);
        vector<vector<int>> intVector = Utils::vecStrToMat(vic2);
        Searchable<Point> *searchable = new SearchableMatrix(start, end, intVector);
        string matrix_problem, solution;
        matrix_problem = accumulate(vic.begin(), vic.end(), matrix_problem);
        if (this->cacheManager->isSavedInCache(matrix_problem)) {
//            cout<< "IN IF STATEMENT - The MATRIX PROBLEM is: " <<endl;
//            cout<< matrix_problem <<endl;
            solution = this->cacheManager->getFromCache(matrix_problem);
//            cout<< "IN IF STATEMENT - The Solution is: " <<endl;
//            cout<< solution <<endl;

        } else {
            // We run each algorithm on the matrix and save the solution
            Searcher<Point> *searcher3 = new BestFs<Point>();
            Searcher<Point> *searcher2 = new Dfs<Point>();
            Searcher<Point> *searcher1 = new Bfs<Point>();
            Searcher<Point> *searcher4 = new Astar<Point>();
            Tester<Point> tester;

            cout<< "THE RESULTS FOR BEST FS ARE: " <<endl;
            SearcherResult searcherResult3 = tester.testSearcher(searcher3, searchable);
            cout<< searcherResult3.numOfEvaluatedNodes <<endl;
            cout<< searcherResult3.cost <<endl;
            cout<< searcherResult3.distance <<endl;
            cout<< searcherResult3.path <<endl;
            data = to_string(searcherResult3.cost) +","+to_string(searcherResult3.distance);
            Utils::writeToFile(data);
            cout<< "THE RESULTS FOR DFS ARE: " <<endl;
            SearcherResult searcherResult2 = tester.testSearcher(searcher2, searchable);
            cout<< searcherResult2.numOfEvaluatedNodes <<endl;
            cout<< searcherResult2.cost <<endl;
            cout<< searcherResult2.distance <<endl;
            cout<< searcherResult2.path <<endl;
            data = to_string(searcherResult2.cost) +","+to_string(searcherResult2.distance);
            Utils::writeToFile(data);
            cout<< "THE RESULTS FOR BFS ARE: " <<endl;
            SearcherResult searcherResult1 = tester.testSearcher(searcher1, searchable);
            cout<< searcherResult1.numOfEvaluatedNodes <<endl;
            cout<< searcherResult1.cost <<endl;
            cout<< searcherResult1.distance <<endl;
            cout<< searcherResult1.path <<endl;
            data = to_string(searcherResult1.cost) +","+to_string(searcherResult1.distance);
            Utils::writeToFile(data);
            cout<< "THE RESULTS FOR A* ARE: " <<endl;
            SearcherResult searcherResult4 = tester.testSearcher(searcher4, searchable);
            cout<< searcherResult4.numOfEvaluatedNodes <<endl;
            cout<< searcherResult4.cost <<endl;
            cout<< searcherResult4.distance <<endl;
            cout<< searcherResult4.path <<endl;
            data = to_string(searcherResult4.cost) +","+to_string(searcherResult4.distance);
            Utils::writeToFile(data);

            solution = searcherResult4.path;
//            cout<< "IN ELSE STATEMENT - The Solution is: " <<endl;
//            cout<< solution <<endl;
            this->cacheManager->saveSLNForProblem(matrix_problem, solution);
            // Delete allocated memory
//            delete searcher1;
//            delete searcher2;
//            delete searcher3;

            //TODO check for better destructor - WORKS PARTIALLY
            delete searcher4;
        }
        // Delete allocated memory
        delete searchable;
        return solution;

    }


};


#endif //SERVER_MYCLIENTHANDLER_H
