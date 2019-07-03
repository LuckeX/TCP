#include "RawTransport.h"
#include <iostream>
#include <boost/array.hpp>
#include "Client.h"

using namespace std;



int main() {
//    RawTransportListener *listen = new RawTransportListenerImpl;
//    RawTransport<TCP> rawTransport(listen);
//    rawTransport.createConnection("0.0.0.0", 9999);
//    rawTransport.listenTo(8889);
//    try {
//        std::cout << "client start." << std::endl;
//        Client cl;
//        cl.run();
//    }
//    catch (std::exception &e){
//        std::cout << e.what() << std::endl;
//    }
//    getchar();

    Server_Client client;
    client.connect("127.0.0.1",8889);
//    char str[]="1000";
//    int x = ntohl(*(reinterpret_cast<uint32_t *>(str)));
//    cout<<x;
    return 0;
}










