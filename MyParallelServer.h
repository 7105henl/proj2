//
// Created by Chen on 1/11/19
//

#ifndef SERVER_MYPARALLELSERVER_H
#define SERVER_MYPARALLELSERVER_H

#include "Server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <unistd.h>

using namespace server_side;
using namespace std;

class MyParallelServer : public Server {
public:
    MyParallelServer() {}

    void open(int port, ClientHandler *handler);

    void stop();

    bool isOpen();

    static vector<string> parseVector(vector<string> vic);
};


#endif //SERVER_MYPARALLELSERVER_H
