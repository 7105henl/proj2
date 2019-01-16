#ifndef SERVER_SEARCHABLE_H
#define SERVER_SEARCHABLE_H

#include <map>
#include <vector>
#include "State.h"
#include "Point.h"

using namespace std;

template<typename T>
class Searchable {
protected:
    State<T> *initialState;
    State<T> *goalState;
    map<T, State<T> *> allStates;

public:
    Searchable(T initial, T goal, map<T, State<T> *> *all) {
        initialState = (*all)[initial];
        goalState = (*all)[goal];
        allStates = (*all);
    }

    virtual State<T> *getInitialState() { return initialState; }

    virtual State<T> *getGoalState() { return goalState; }

    virtual vector<State<T> *> getAllPossibleStates(State<T> *pred);

    virtual ~Searchable() {
        for (typename map<T, State<T> *>::iterator it = allStates.begin(); it != allStates.end(); ++it) {
            delete it->second;
        }
    }

};


#endif //SERVER_SEARCHABLE_H
