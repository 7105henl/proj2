
#ifndef SERVER_SEARCHERSOLVER_H
#define SERVER_SEARCHERSOLVER_H


#include "Solver.h"
#include "SearcherResult.h"
#include "Searchable.h"
#include "Searcher.h"

template<typename T>
class SearcherSolver : public Solver<SearcherResult, Searchable<T>> {
private:
    Searcher<T> *searcher;
public:
    // Default constructor, the searcher will updated in run-time according to selected algorithm we want to inject
    //SearcherSolver() {}
    SearcherSolver<T>() {}

    SearcherResult solve(Searchable<T> *searchable) {
        return searcher->search(searchable);
    }

    void setSearcher(Searcher<T> *searcher) {
        SearcherSolver::searcher = searcher;

    }

};


#endif //SERVER_SEARCHERSOLVER_H
