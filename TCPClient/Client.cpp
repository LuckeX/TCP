//
// Created by xyk on 19-7-3.
//

#include "Client.h"

void Server_Client::listento(int port) {
    if(sock)cout<<"TCP sock existed, ignoring the listening request for port "<<port<<endl;
    else{
        sock.reset(new tcp::socket(m_io));
        m_acceptor.reset(new tcp::acceptor(m_io,tcp::endpoint(tcp::v4(),port)));
        m_acceptor->async_accept(*sock,std::bind(&Server_Client::accept_handler,
                                                 this, std::placeholders::_1,sock));
        cout<<"TCP listening on "<<m_acceptor->local_endpoint().address().to_string()<<":"<<port<<endl;
    }
    m_io.run();
}

void Server_Client::accept_handler(const boost::system::error_code &ec, Server_Client::sock_ptr sock) {
    if (ec) { return; }
    std::cout << "client:";
    std::cout << sock->remote_endpoint().address() << std::endl;
    sock->async_write_some(boost::asio::buffer("hello asio"), std::bind(&Server_Client::write_handler, this, std::placeholders::_1));
}

void Server_Client::connect(const char *address, int port) {
     if(sock)cout<<"TCP sock is existed"<<endl;
     else{
         sock.reset(new tcp::socket(m_io));
         tcp::endpoint m_ep(boost::asio::ip::address::from_string(address),port);
         sock->async_connect(m_ep, std::bind(&Server_Client::connect_handler, this, std::placeholders::_1, sock));
         m_io.run();
     }
}

void Server_Client::connect_handler(const boost::system::error_code &ec, Server_Client::sock_ptr sock) {
    if(ec){
        cout<<"error:"<<ec.message()<<endl;
        return;
    }
    cout<<"connected"<<endl;
    char str[] = "1234567";
    while(1){
        sendData(str,5);
        sleep(1);
    }

//    sock->async_write_some(boost::asio::buffer("hello"),std::bind(&Server_Client::write_handler,this,std::placeholders::_1));
}

void Server_Client::sendData(char *buf, int len) {
    sock->async_write_some(boost::asio::buffer(buf,len),std::bind(&Server_Client::write_handler,this,std::placeholders::_1));
}