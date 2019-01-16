#ifndef SERVER_ASTAR_H
#define SERVER_ASTAR_H

#include <stack>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <set>
#include "Utils.h"

#include "Searcher.h"

template<typename T>
class Astar : public Searcher<T> {
public:
    SearcherResult search(Searchable<T> *searchable) {
        State<T> *initial = searchable->getInitialState();
        State<T> *goal = searchable->getGoalState();

        // If the destination is the same as source
        if (initial->getState() == goal->getState()) {
            return Utils::getSearcherResult(*initial, 1);
        }

        map<T, int> visited;
        visited[initial->getState()] = initial->getCost();

        set<State<T> *> openList;
        openList.insert(initial);

        while (!openList.empty()) {
            State<T> *curr = *openList.begin();

            // Remove this vertex from the open list
            openList.erase(openList.begin());

            vector<State<T> *> nextStates = searchable->getAllPossibleStates(curr);

            for (int i = 0; i < nextStates.size(); i++) {
                State<T> *next = nextStates[i];
                int fWhatIf = visited[curr->getState()] + next->getCost() + 1;

                if (next->getPrevious() == NULL && visited.count(next->getState()) == 0) {
                    next->setPrevious(curr);
                    visited[next->getState()] = fWhatIf;
                    openList.insert(next);
                } else if (openList.count(next) == 1 && fWhatIf < visited[next->getState()]) {
                    next->setPrevious(curr);
                    visited[next->getState()] = fWhatIf;
                    //dont insert, already in
                }
            }
        }

        if (goal->getPrevious() == NULL) {
            return {-1, -1};
        }
        return Utils::getSearcherResult(*goal, visited.size());
    }
};

#endif //SERVER_ASTAR_H
