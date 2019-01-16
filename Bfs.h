#ifndef SERVER_BFS_H
#define SERVER_BFS_H

#include <list>
#include <iostream>
#include <queue>
#include <cstring>
#include "Utils.h"
#include "State.h"

#include "Searcher.h"

template<typename T>
class Bfs : public virtual Searcher<T> {
public:
    SearcherResult search(Searchable<T> *searchable) {
        State<T> *initial = searchable->getInitialState();
        State<T> *goal = searchable->getGoalState();

        // If the destination is the same as source
        if (initial->getState() == goal->getState()) {
            return Utils::getSearcherResult(*initial, 1);
        }

        // Mark all the vertices as not visited
        map<T, bool> visited;
        visited[initial->getState()] = true;

        // Create a queue
        queue<State<T> *> open;
        // Enqueue initial state
        open.push(initial);

        // Do a BFS starting from initial state
        while (!open.empty()) {
            State<T> *curr = open.front();

            // If we have reached the goal state, we are done
            if (curr->getState() == goal->getState()) {
                return Utils::getSearcherResult(*curr, visited.size());
            }

            // Otherwise dequeue the state in the queue and enqueue its adjacent states
            open.pop();

            vector<State<T> *> nextStates = searchable->getAllPossibleStates(curr);

            for (int i = 0; i < nextStates.size(); i++) {
                State<T> *state = nextStates[i];
                T next = state->getState();

                // if adjacent state is valid, has path and not visited yet, enqueue it.
                if (!visited[next]) {
                    // mark state as visited and enqueue it
                    visited[next] = true;
                    state->setPrevious(curr);
                    open.push(state);
                }
            }
        }

        // Return -1 if destination cannot be reached
        return {-1, -1};
    }
};


#endif //SERVER_BFS_H
