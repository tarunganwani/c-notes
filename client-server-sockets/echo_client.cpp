#include <bits/stdc++.h>
#include <sys/socket.h>
#include "util.h"

using namespace std;

int main(){
    //LIFECYCLE - create(socket) connect send/recv

    //CREATE
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1){
        print_error_and_exit("Failed create socket");
    }

     // Server address and port
    std::string serverIP = "127.0.0.1";
    int serverPort = 8080;

    // Configure server details
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIP.c_str(), &(serverAddress.sin_addr));

    //CONNECT
    if(connect(socketfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        print_error_and_exit("Failed to conenct to server");
        close(socketfd);
    }
    print_info("Conneted to server @ localhost 8080..");

    char recdbuf[1024];
    string sendbuf, recdbufstr, msg;
    
    //SEND and RECV loop
    while(1){
    
        memset(recdbuf, 0, 1024);
        if(recv(socketfd, recdbuf,sizeof(recdbuf), 0) == -1){
            print_error("Error receiving data from server");
        }
    
        recdbufstr = string(recdbuf);
        msg = "Msg received = \"" + recdbufstr + "\"";
        recdbufstr = recdbufstr.substr(0, recdbufstr.find_first_of('\n') -1);
        print_info(msg.c_str());
    
        cout << "Enter message to send > ";
        cin >> sendbuf;
        
        sendbuf = sendbuf.substr(0, sendbuf.find_first_of('\n') - 1);
        // msg = "user msg to send \""+sendbuf + "\"";
        // print_info(msg.c_str());

        if(send(socketfd, sendbuf.c_str(), sendbuf.length(), 0) == -1){
            print_error("Failed to send data to server");
        }
        msg = "Msg sent =  \"" + sendbuf + "\"";
        print_info(msg.c_str());
    }
    return 0;
}