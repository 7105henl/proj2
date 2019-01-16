

#ifndef SERVER_SEARCHER_H
#define SERVER_SEARCHER_H

#include <vector>
#include "Searchable.h"
#include "SearcherResult.h"

using namespace std;

template<typename T>
class Searcher {
public:
    virtual SearcherResult search(Searchable<T> *searchable) = 0;
    virtual ~Searcher(){}

};

#endif //SERVER_SEARCHER_H
