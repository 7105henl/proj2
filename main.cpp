#include <iostream>
#include "FileCacheManager.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
//#include "StringReverser.h"
#include "SearchableMatrix.h"
#include "Point.h"
//#include "Bfs.h"
//#include "Dfs.h"
//#include "Astar.h"
//#include "BestFs.h"
#include "Tester.h"
#include "MyParallelServer.h"
#include "SearcherSolver.h"
#include <ctime>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /** This program runs parallel server */

    /**  New Solver with Object Adapter "Searcher-solver" injected (for algorithm-to-matrix)  **/
    Solver<SearcherResult, Searchable<Point>> *solver = new SearcherSolver<Point>();
    /**  New Cache Manager with File manager injected  **/
    CacheManager<string, string> *cacheManager = new FileCacheManager<string, string>();
    /**  New Server with parallel server injected  **/
    Server *parallelServer = new MyParallelServer();
    /**  New Client with MyClientHandler injected  **/
    ClientHandler *clientHandler = new MyClientHandler<SearcherResult, Searchable<Point>>(solver, cacheManager);
    /**  Start the server on specific client handler**/
    parallelServer->open(stoi(argv[1]), clientHandler);


    // Delete allocated memory
    delete cacheManager;
    delete solver;
    delete parallelServer;
    delete clientHandler;
    return 0;
}