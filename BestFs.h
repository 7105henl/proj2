#ifndef SERVER_BESTFS_H
#define SERVER_BESTFS_H

#include <queue>
#include "Searcher.h"
#include "Utils.h"
#include "UpdatablePriorityQueue.h"

using namespace better_priority_queue;

template<typename T>
class BestFs : public Searcher<T> {
public:
    SearcherResult search(Searchable<T> *searchable) {
        State<T> *initial = searchable->getInitialState();
        State<T> *goal = searchable->getGoalState();

        // If the destination is the same as source
        if (initial->getState() == goal->getState()) {
            return Utils::getSearcherResult(*initial, 1);
        }

        // Create a priority queue
        UpdatablePriorityQueue<State<T> *, int> open;
        map<T, int> visited;
        visited[initial->getState()] = initial->getCost();
        // Enqueue initial state
        open.push(initial, initial->getCost(), true);

        while (!open.empty()) {
            PriorityQueueNode<State<T> *, int> curr = open.pop_value();
            vector<State<T> *> nextStates = searchable->getAllPossibleStates(curr.key);

            for (int i = 0; i < nextStates.size(); i++) {
                State<T> *nextState = nextStates[i];
                T next = nextState->getState();

                int whatIf = curr.priority + nextState->getCost() + 1;

                if (nextState->getPrevious() == NULL && visited.count(next) == 0) {
                    nextState->setPrevious(curr.key);
                    visited[next] = whatIf;
                    open.push(nextState, whatIf, true);
                } else if (open.exists(nextState) && whatIf < visited[next]) {
                    nextState->setPrevious(curr.key);
                    visited[next] = whatIf;
                    open.update(nextState, whatIf);
                }
            }
        }

        if (goal->getPrevious() == NULL) {
            return {-1, -1};
        }
        return Utils::getSearcherResult(*goal, visited.size());
    }
};


#endif //SERVER_BESTFS_H
