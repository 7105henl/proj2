
#include <algorithm>
#include "StringReverser.h"


string StringReverser::solve(string problem) {
    string str;
    for (string::iterator i = problem.begin(); i != str.end(); ++i) {
        if (*i == '\n' || *i == '\r' || *i == '\0') {
            continue;
        }
        str += *i;
    }
    reverse(str.begin(), str.end());
    return str;
}