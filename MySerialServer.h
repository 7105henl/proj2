//
// Created by Chen on 02-Jan-19.
//

#ifndef SERVER_MYSERIALSERVER_H
#define SERVER_MYSERIALSERVER_H

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

class MySerialServer : public Server {

public:
    MySerialServer() {}

    void open(int port, ClientHandler *ch);

    void stop();

    bool isOpen();
};


#endif //SERVER_MYSERIALSERVER_H
