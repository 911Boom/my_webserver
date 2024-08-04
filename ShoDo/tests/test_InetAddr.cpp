//
// Created by 着魔之人 on 24-7-4.
//
#include "server/InetAddr.cpp"
#include <iostream>
using namespace std;


int main() {
    auto *addr = new InetAddr(StringArg("127.0.0.1"),8080);

    cout<<InetAddr::HostNameToInetAddr(StringArg("www.codeforces.com"),addr)<<endl;
    cout<<addr->toIpPort()<<endl;
    return 0;
}
