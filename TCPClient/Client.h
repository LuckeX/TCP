//
// Created by xyk on 19-7-3.
//

#ifndef TCPCLIENT_CLIENT_H
#define TCPCLIENT_CLIENT_H
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>

using boost::asio::ip::tcp;
using namespace std;


class Server_Client {
    typedef tcp::socket socket_type;
    typedef std::shared_ptr <socket_type> sock_ptr;
    typedef std::shared_ptr <tcp::acceptor> acceptor_ptr;

public:
    void listento(int port);
    void connect(const char *address,int port);

private:

    void accept_handler(const boost::system::error_code &ec, sock_ptr sock);

    void write_handler(const boost::system::error_code &) { std::cout << "send msg complete." << std::endl; }

    void connect_handler(const boost::system::error_code &ec, sock_ptr sock);

    void sendData(char* buf,int len);

private:
    boost::asio::io_service m_io;
    acceptor_ptr m_acceptor;
    sock_ptr sock;
};


#endif //TCPCLIENT_CLIENT_H
