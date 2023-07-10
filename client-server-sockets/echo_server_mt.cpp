#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "util.h"

using namespace std;
/*
    from util.h

    void print_info(const char *msg);
    void print_error(const char *err);
    void print_error_and_exit(const char *err);
    string getIPPortFromSocketAddress(const sockaddr_in& socketAddress);
*/

struct threadargs{
    int serversocketfd;
    int clientsocketfd;
};

void sendrecvFunction(threadargs t){

    auto myid = this_thread::get_id();
    stringstream ss;
    ss << myid;
    auto threadidStr = ss.str();

    string buf, msg;
    char recdbuf[1024];
    int bytessent = 0, bytesrecd = 0;
    buf = "[" + threadidStr + "] Hello from echo server.. Write any text for echo and END for exit\n\n>" ;

    while(1){

        bytessent = send(t.clientsocketfd, buf.c_str(), buf.length(), 0);
        if(bytessent == -1){
            close(t.clientsocketfd);
            close(t.serversocketfd);
            msg = "[" + threadidStr + "] Failed sending data to client";
            print_error(msg.c_str());
        }

        bytesrecd = recv(t.clientsocketfd, recdbuf, sizeof(recdbuf), 0);
         if(bytesrecd == -1){
            close(t.clientsocketfd);
            close(t.serversocketfd);
            msg = "[" + threadidStr + "] Failed getting data from client";
            print_error(msg.c_str());
        }

        msg = "[" + threadidStr + "] bytes received = " + to_string(bytesrecd);
        print_info(msg.c_str());
        buf = string(recdbuf);
        buf = buf.substr(0, bytesrecd);

        if(buf =="END"){
            msg = "[" + threadidStr + "] RECD END SIGNAL. BYE!";
            print_info(msg.c_str());
            close(t.clientsocketfd);
            close(t.serversocketfd);
            return;
        }

        string msg = "[" + threadidStr + "] Got data from client \"" + buf + "\"";
        print_info(msg.c_str());
    }
}

int main() {

    //LIFECYCLE - create bind listen accept

    //CREATE
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1){
        print_error_and_exit("Failed create socket");
    }

    //BIND to IP address and port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);  // Port number
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Bind to any available network interface

    if(bind(socketfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1){
        close(socketfd);
        print_error_and_exit("Failed to bind to address");
    }


    //LISTEN for incoming connections
    if(listen(socketfd, 2) == -1){
        close(socketfd);
        print_error_and_exit("Failed to listen on 8080");
    }

    print_info("server listening for connections..");

    // Accept incoming connections
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress); 
    while(1){
        int clientsocketfd = accept(socketfd, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if(clientsocketfd == -1){
            print_error_and_exit("Failed to accept incoming conenction");
        }
        string msg = "Got connection from " + getIPPortFromSocketAddress(clientAddress);
        print_info(msg.c_str());
        auto clientthread = thread(sendrecvFunction, threadargs{socketfd, clientsocketfd});
        clientthread.detach();
    }    

    return 0;
}