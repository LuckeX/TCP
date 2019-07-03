//
// Created by xyk on 19-7-3.
//

#include "Server.h"

static const int BUFFER_ALIGNMENT = 16;
static const double BUFFER_EXPANSION_MULTIPLIER = 1.3;

Server_Client::Server_Client(size_t initialBufferSize, bool tag){
    m_isClosing = false;
    m_tag = tag;
    m_bufferSize = initialBufferSize;
    m_receivedBytes = 0;
}

void Server_Client::accept_handler(const boost::system::error_code &ec, Server_Client::sock_ptr sock) {
    if (ec) { return; }
    std::cout << "client:";
    std::cout << sock->remote_endpoint().address() << std::endl;
//    sock->async_write_some(boost::asio::buffer("hello asio"), std::bind(&Server_Client::write_handler, this, std::placeholders::_1));
    receiveData();
}

void Server_Client::readPacketHandler(const boost::system::error_code &ec, std::size_t bytes) {
    if (m_isClosing)
        return;

    printf("Port#%d recieved data(%zu)", m_acceptor->local_endpoint().port(), bytes);
    uint32_t expectedLen = ntohl(*(reinterpret_cast<uint32_t *>(m_readHeader)));
    if (!ec || ec == boost::asio::error::message_size) {
        m_receivedBytes += bytes;
        if (expectedLen > m_receivedBytes) {
            printf("Expect to receive %u bytes, but actually received %zu bytes.", expectedLen, bytes);
            printf("Continue receiving %u bytes.", expectedLen - m_receivedBytes);
            sock->async_read_some(
                    boost::asio::buffer(m_receiveData.buffer.get() + m_receivedBytes, expectedLen - m_receivedBytes),
                    boost::bind(&Server_Client::readPacketHandler, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
        } else {
            m_receivedBytes = 0;
            receiveData();
        }
    } else {
        printf("Error receiving data: %s", ec.message().c_str());
    }
}

void Server_Client::readHandler(const boost::system::error_code &ec, std::size_t bytes) {
    if (m_isClosing)return;

    if (!ec || ec == boost::asio::error::message_size) {
        if (!m_tag) {
            receiveData();
            return;
        }
        uint32_t payloadlen = 0;
        assert(sock);
        m_receivedBytes += bytes;
        if (m_receivedBytes < 4) {
            printf("Incomplete header, continue receiving %u bytes\n", 4 - m_receivedBytes);
            sock->async_read_some(boost::asio::buffer(m_readHeader + m_receivedBytes, 4 - m_receivedBytes),
                                  boost::bind(&Server_Client::readHandler, this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
        } else {
            payloadlen = ntohl(*(reinterpret_cast<uint32_t *>(m_readHeader)));
            if (payloadlen > m_bufferSize) {
                m_bufferSize = ((payloadlen * BUFFER_EXPANSION_MULTIPLIER + BUFFER_ALIGNMENT - 1) / BUFFER_ALIGNMENT) *
                               BUFFER_ALIGNMENT;
                printf("Increasing the buffer size: %zu\n", m_bufferSize);
                m_receiveData.buffer.reset(new char[m_bufferSize]);
            }
            printf("readHandler(%zu):[%x,%x,%x,%x], payloadlen:%u", bytes, m_readHeader[0], m_readHeader[1],
                   (unsigned char) m_readHeader[2], (unsigned char) m_readHeader[3], payloadlen);

            m_receivedBytes = 0;
            sock->async_read_some(boost::asio::buffer(m_receiveData.buffer.get(), payloadlen),
                                  boost::bind(&Server_Client::readPacketHandler, this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
        }
    }
    cout << m_buf << "  " << bytes << endl;
    receiveData();
}

void Server_Client::receiveData() {
//    sock->async_read_some(boost::asio::buffer(m_buf), std::bind(&Server_Client::read_handler, this, std::placeholders::_1));
//       sock->async_read_some(boost::asio::buffer(m_buf),boost::bind(&Server_Client::readHandler,this,
//               boost::asio::placeholders::error,
//               boost::asio::placeholders::bytes_transferred));

    if (!m_receiveData.buffer)
        m_receiveData.buffer.reset(new char[m_bufferSize]);

    assert(sock);
    if (m_tag) {
        //TODO
    } else {
        sock->async_read_some(boost::asio::buffer(m_buf), boost::bind(&Server_Client::readHandler, this,
                                                                      boost::asio::placeholders::error,
                                                                      boost::asio::placeholders::bytes_transferred));
    }
}

void Server_Client::read_handler(const boost::system::error_code &ec) {
    if (ec) {
        cout << "error:" << ec.message() << endl;
        return;
    }
    cout << m_buf << endl;
    receiveData();
}

void Server_Client::connect(const char *address, int port) {
    if (sock)cout << "TCP sock is existed" << endl;
    else {
        sock.reset(new tcp::socket(m_io));
        tcp::endpoint m_ep(boost::asio::ip::address::from_string(address), port);
        sock->async_connect(m_ep, std::bind(&Server_Client::connect_handler, this, std::placeholders::_1, sock));
        m_io.run();
    }
}

void Server_Client::connect_handler(const boost::system::error_code &ec, Server_Client::sock_ptr sock) {
    if (ec) {
        cout << "error:" << ec.message() << endl;
        return;
    }
    cout << "connected" << endl;
    char *str = "hello";
    while (1) {
        sendData(str, 5);
        sleep(1);
    }
}

void Server_Client::sendData(char *buf, int len) {
    sock->async_write_some(boost::asio::buffer("hello"),
                           std::bind(&Server_Client::write_handler, this, std::placeholders::_1));
}












