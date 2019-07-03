#include "RawTransport.h"
#include <iostream>
#include <boost/array.hpp>
#include "Client.h"

using namespace std;
using namespace boost::asio;

class Client {
    typedef ip::tcp::socket socket_type;
    typedef std::shared_ptr<socket_type> sock_ptr;
public:
    Client() : m_ep(ip::address::from_string("127.0.0.1"), 9998) { start(); }

    void run() { m_io.run(); }

private:
    sock_ptr sock;
    void start() {
        sock.reset(new socket_type(m_io));
        sock->async_connect(m_ep, std::bind(&Client::connect_handler, this, std::placeholders::_1, sock));
    }

    void connect_handler(const boost::system::error_code &ec, sock_ptr sock) {
        if (ec) { return; }
        std::cout << "receive from:" << sock->remote_endpoint().address() << std::endl;
        sock->async_read_some(buffer(m_buf), std::bind(&Client::read_handler, this, std::placeholders::_1));
//        sock->async_write_some(boost::asio::buffer("hello asio"), std::bind(&Client::write_handler, this, std::placeholders::_1));
    }

    void read_handler(const boost::system::error_code &ec) {
        if (ec) {
            cout<<ec.message()<<endl;return;
        }
        cout<<m_buf<<endl;
    }

private:
    io_service m_io;
    ip::tcp::endpoint m_ep;
    enum {
        max_length = 1024
    };
    char m_buf[max_length];
};


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
//    const char *addr="localhost";
    client.connect("127.0.0.1",8889);
    return 0;
}