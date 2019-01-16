#ifndef SERVER_DFS_H
#define SERVER_DFS_H

#include <cstring>
#include <string>
#include "Utils.h"
#include "Searcher.h"

template<typename T>
class Dfs : public Searcher<T> {
public:
    SearcherResult search(Searchable<T> *searchable) {
        State<T> *initial = searchable->getInitialState();
        State<T> *goal = searchable->getGoalState();

        // If the destination is the same as source
        if (initial->getState() == goal->getState()) {
            return Utils::getSearcherResult(*initial, 1);
        }

        // Initially mark all vertices as not visited
        map<T, bool> visited;

        // Create a stack for DFS
        stack<State<T>*> stack;

        // Push the current source node.
        stack.push(initial);
        visited[initial->getState()] = true;

        while (!stack.empty())
        {
            // Pop a vertex from stack and print it
            State<T>* curr = stack.top();
            stack.pop();

            // Get all adjacent vertices of the popped vertex s
            // If a adjacent has not been visited, then puah it
            // to the stack.
            vector<State<T>*> nextStates = searchable->getAllPossibleStates(curr);

            for(int i = 0; i < nextStates.size(); ++i) {
                State<T> *state = nextStates[i];
                T next = state->getState();

                if(next == goal->getState()) {
                    state->setPrevious(curr);
                    return Utils::getSearcherResult(*state, visited.size());
                }

                // if adjacent state is valid, has path and not visited yet, enqueue it.
                if (!visited[next]) {
                    // mark state as visited and enqueue it
                    visited[next] = true;
                    state->setPrevious(curr);
                    stack.push(state);
                }
            }
        }

        return {-1, -1};
    }
};


#endif //SERVER_DFS_H
