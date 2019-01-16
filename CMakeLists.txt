cmake_minimum_required(VERSION 3.13)
project(GenericServer_master_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proj2
        Astar.h
        BestFs.h
        Bfs.h
        CacheManager.h
        ClientHandler.h
        Dfs.h
        FileCacheManager.h
        main.cpp
        MyClientHandler.h
        MyParallelServer.cpp
        MyParallelServer.h
        MySerialServer.cpp
        MySerialServer.h
        MyTestClientHandler.cpp
        MyTestClientHandler.h
        Point.h
        Searchable.h
        SearchableMatrix.cpp
        SearchableMatrix.h
        Searcher.h
        SearcherResult.h
        SearcherSolver.h
        Server.h
        Solver.h
        State.h
        StringReverser.cpp
        StringReverser.h
        Tester.h
        UpdatablePriorityQueue.h
        Utils.cpp
        Utils.h)
