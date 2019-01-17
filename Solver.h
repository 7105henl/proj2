#ifndef SERVER_SOLVER_H
#define SERVER_SOLVER_H

template<typename Solution, typename Problem>
class Solver {
public:
    virtual Solution solve(Problem *p) = 0;
    ~Solver() = default;
};


#endif //SERVER_SOLVER_H
