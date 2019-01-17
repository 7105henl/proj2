
#include <vector>
#include "MyParallelServer.h"
#include <string>
#include <cstring>
#include <string.h>

const char OS_Delimiter = '\n';


using std::string;
using std::stringstream;


class my_thread_info {
public:
    int serverSocket;
    int clientSocket;
    ClientHandler *clientHandler;
};

vector<string> MyParallelServer::parseVector(vector<string> vic1) {
    vector<string> parsedVector;
    string temp;
    for (vector<string>::iterator it = vic1.begin(); it < vic1.end(); ++it) {
        for (char &ch: *it) {
            if (ch == '\n') {
                parsedVector.push_back(temp);
                temp = "";
            } else if (ch == 'e') {
                return parsedVector;
            } else if (ch == '\r') {
                continue;
            } else {
                temp += ch;
            }
        }
    }
}

static void *connectionHandler(void *context) {
    my_thread_info info = *((my_thread_info *) context);
    vector<string> bufferVector;
    //Accept and incoming connection
//    puts("Waiting for incoming connections...");
    bool continueReading = true;
    while (continueReading) {
        char buffer[4096] = {0};
        read(info.clientSocket, buffer, sizeof(buffer));
        if (buffer[0] != '\0') {
            string s = buffer;
            bufferVector.push_back(buffer);
            if (s.find("end") != string::npos) {
                vector<string> final = MyParallelServer::parseVector(bufferVector);
                string solution = info.clientHandler->handleClient(final);
                solution += '\n';
                send(info.clientSocket, solution.c_str(), strlen(solution.c_str()), 0);
                bufferVector.clear();
//                bzero(buffer,sizeof(buffer)); //bzero for buffer - for saving the project not to explode
            }
        }
    }
}


void MyParallelServer::open(int port, ClientHandler *handler) {
    int opt = 1;
    struct sockaddr_in server, client;
    int serverDescriptor;

    // Creating serverSocket file descriptor
    if ((serverDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
        perror("serverSocket failed");
        exit(EXIT_FAILURE);
    }

    // Create timeout for incoming connection
    timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    setsockopt(serverDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Forcefully attaching serverSocket to port
    if (::bind(serverDescriptor, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serverDescriptor, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //Accept and incoming connection
//    cout << ("Waiting for incoming connections...") << endl;
    int indexOfThread = 0;
    pthread_t threadId[50];
    int acceptConnection;
    bool first_client = true;
    while (true) {
        socklen_t addrlen = sizeof(sockaddr_in);
        // This is endless loop for first client, by design we wait infinity
        if (first_client) {
            while (true) {
                acceptConnection = accept(serverDescriptor, (struct sockaddr *) &client, &addrlen);
                if (acceptConnection < 0) {
                    continue;
                } else {
                    first_client = false;
                    break;
                }
            }
        } else { // not first client, has timeout for connect
            acceptConnection = accept(serverDescriptor, (struct sockaddr *) &client, &addrlen);
            if (acceptConnection < 0) {
                if (errno == EWOULDBLOCK) {
                    cout << "timeout!" << endl;
                    break;
                } else {
                    break;
                }
            } else {
//                cout << "Connection accepted, starting listener thread" << endl;
            }
        }

        my_thread_info info;
        info.serverSocket = serverDescriptor;
        info.clientHandler = handler;
        info.clientSocket = acceptConnection;

        int index = pthread_create(&threadId[indexOfThread], NULL, connectionHandler, (void *) &info);
        if (index < 0) {
            perror("could not create thread");
            exit(EXIT_FAILURE);
        }
        indexOfThread++;
    }
    // If connection timeout, wait for other thread to finish calculating
    for (int j = 0; j < indexOfThread; j++) {
        pthread_join(threadId[j], NULL);
    }

    // Close connection
    close(acceptConnection);
    close(serverDescriptor);


}

void MyParallelServer::stop() {

}

bool MyParallelServer::isOpen() {

}