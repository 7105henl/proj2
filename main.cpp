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
    Solver<SearcherResult, Searchable<Point>> *solver = new SearcherSolver<Point>();
    CacheManager<string, string> *cacheManager = new FileCacheManager<string, string>();
    Server *parallelServer = new MyParallelServer();
    ClientHandler *clientHandler = new MyClientHandler<SearcherResult, Searchable<Point>>(solver, cacheManager);
    parallelServer->open(stoi(argv[1]), clientHandler);

    // TODO - create destructor and Delete allocated memory (OPTIONAL HERE)
    return 0;
}