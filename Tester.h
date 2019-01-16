
#ifndef SERVER_TESTER_H
#define SERVER_TESTER_H


#include "Searcher.h"
#include "Dfs.h"
#include "Searchable.h"
#include "SearcherResult.h"

template<typename T>
class Tester {
public:
    SearcherResult testSearcher(Searcher<T> *searcher, Searchable<T> *searchable) {
        SearcherResult solution = searcher->search(searchable);
        return solution;
    }

};


#endif //SERVER_TESTER_H
