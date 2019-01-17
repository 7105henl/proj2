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
            Searcher<Point> *pBestFSSearcher = new BestFs<Point>();
//            Searcher<Point> *pDfsSearcher = new Dfs<Point>();
//            Searcher<Point> *pBfsSearcher = new Bfs<Point>();
//            Searcher<Point> *pAstarSearcher = new Astar<Point>();
            Tester<Point> tester;

//            cout<< "THE RESULTS FOR BEST FS ARE: " <<endl;
            SearcherResult pBestFSResult = tester.testSearcher(pBestFSSearcher, searchable);
//            cout<< pBestFSResult.numOfEvaluatedNodes <<endl;
//            cout<< pBestFSResult.cost <<endl;
//            cout<< pBestFSResult.distance <<endl;
//            cout<< pBestFSResult.path <<endl;
//            data = to_string(pBestFSResult.cost) +","+to_string(pBestFSResult.distance);
//            Utils::writeToFile(data);
//            cout<< "THE RESULTS FOR DFS ARE: " <<endl;
//            SearcherResult pDfsResult = tester.testSearcher(pDfsSearcher, searchable);
//            cout<< pDfsResult.numOfEvaluatedNodes <<endl;
//            cout<< pDfsResult.cost <<endl;
//            cout<< pDfsResult.distance <<endl;
//            cout<< pDfsResult.path <<endl;
//            data = to_string(pDfsResult.cost) +","+to_string(pDfsResult.distance);
//            Utils::writeToFile(data);
//            cout<< "THE RESULTS FOR BFS ARE: " <<endl;
//            SearcherResult pBfsResult = tester.testSearcher(pBfsSearcher, searchable);
//            cout<< pBfsResult.numOfEvaluatedNodes <<endl;
//            cout<< pBfsResult.cost <<endl;
//            cout<< pBfsResult.distance <<endl;
//            cout<< pBfsResult.path <<endl;
//            data = to_string(pBfsResult.cost) +","+to_string(pBfsResult.distance);
//            Utils::writeToFile(data);
//            cout<< "THE RESULTS FOR A* ARE: " <<endl;
//            SearcherResult pAstarResult = tester.testSearcher(pAstarSearcher, searchable);
//            cout<< pAstarResult.numOfEvaluatedNodes <<endl;
//            cout<< pAstarResult.cost <<endl;
//            cout<< pAstarResult.distance <<endl;
//            cout<< pAstarResult.path <<endl;
//            data = to_string(pAstarResult.cost) +","+to_string(pAstarResult.distance);
//            Utils::writeToFile(data);

            solution = pBestFSResult.path;
//            cout<< "IN ELSE STATEMENT - The Solution is: " <<endl;
//            cout<< solution <<endl;
            this->cacheManager->saveSLNForProblem(matrix_problem, solution);
            // Delete allocated memory
//            delete pBfsSearcher;
//            delete pDfsSearcher;
//            delete pBestFSSearcher;

            //TODO check for better destructor - WORKS PARTIALLY
            delete pBestFSSearcher;
        }
        // Delete allocated memory
        delete searchable;
        return solution;

    }


};


#endif //SERVER_MYCLIENTHANDLER_H
