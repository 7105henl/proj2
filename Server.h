#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "ClientHandler.h"

using namespace std;
namespace server_side {

    class Server {
    public:

        virtual void open(int port, ClientHandler* clientHandler)= 0;

        virtual void stop()= 0;

        virtual bool isOpen()= 0;
    };
}


#endif //SERVER_SERVER_H
