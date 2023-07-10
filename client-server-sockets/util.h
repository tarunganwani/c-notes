#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using std::cout;
using std::cerr;
using std::endl;
using std::string;

void print_info(const char *msg) {
    cout << "INFO : " << msg << endl;
}

void print_error(const char *err){
    cerr << "ERROR : " <<  err << endl;
}

void print_error_and_exit(const char *err){
    print_error(err);
    exit(-1);
}

string getIPPortFromSocketAddress(const sockaddr_in& socketAddress) {
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(socketAddress.sin_addr), ip, INET_ADDRSTRLEN);
    return "Address: " + string(ip) + " Port : " + std::to_string(ntohs(socketAddress.sin_port));
}