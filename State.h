#ifndef SERVER_STATE_H
#define SERVER_STATE_H

#include <string>
#include <cstring>

using namespace std;

template<typename T>
class State {
private:
    T state;
    int cost;
    string details;
    State<T> *cameFrom = NULL;
public:
    State() {}

    State(T state) { setState(state); }

    State(T state, int cost, string points) {
        setState(state);
        this->cost = cost;
        this->details = points;
    }

    void setState(T state) { this->state = state; }

    int getCost() { return cost; }

    State<T> *getPrevious() { return cameFrom; }

    void setPrevious(State<T> *state) { this->cameFrom = state; }

    T getState() { return state; }

    friend bool operator<(const State<T> l, const State<T> r) {
        return l.state < r.state;
    }

    const string getDetails() {
        return details;
    }
};


#endif //SERVER_STATE_H
