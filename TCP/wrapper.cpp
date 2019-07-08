//
// Created by xyk on 19-6-19.
//

#include "wrapper.h"
#include "Server.h"
#include <iostream>
#include <queue>


using namespace std;

void call_listento(int port){
    Server_Client server_client(5, false);
    server_client.listento(port);
}

void *call_getBuffer(){
    if(!Server_Client::m_receiveQueue.empty()){
        boost::lock_guard<boost::mutex>lock(Server_Client::m_receiveQueueMutex);
        void *p = Server_Client::m_receiveQueue.front().buffer.get();
//        cout<< static_cast<char*>(p)<<endl;
        Server_Client::m_receiveQueue.pop();
        return p;
    }
    return NULL;
}

void call_connect(char* ip,int port){

}