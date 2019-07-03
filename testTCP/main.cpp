#include "RawTransport.h"
#include <iostream>
#include "Server.h"
using namespace std;



int main() {
//    RawTransportListener *listen = new RawTransportListenerImpl();
//    RawTransport <UDP> rawTransport(listen);
////    rawTransport.createConnection("localhost",8889);
//    rawTransport.listenTo(9998);
//    try {
//        cout << "server listening" << endl;
//        Server_Client svr;
//        svr.listento(9998);
//    } catch (exception &e) { cout << e.what() << endl; }
//    return 0;
      Server_Client client(5, true);
      client.listento(8889);
}