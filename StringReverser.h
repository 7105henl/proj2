
#ifndef SERVER_STRINGREVERSER_H
#define SERVER_STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include "Utils.h"

using namespace std;

class StringReverser : public Solver<string, string> {

    string solve(string problem);
};


#endif //SERVER_STRINGREVERSER_H
