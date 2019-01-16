#ifndef SERVER_CLIENTHANDLER_H
#define SERVER_CLIENTHANDLER_H

#include <iostream>
#include <ostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class ClientHandler {

public:

    virtual string handleClient(vector<std::string> buffer) = 0;
};


#endif //SERVER_CLIENTHANDLER_H
