#ifndef SOCKET_H
#define SOCKET_H

#include "Message.h"
#include <QTcpSocket>

class Socket : private QTcpSocket{
public:
    Socket(const qintptr socketDescriptor);
    ~Socket();

    void sendMessage(const Message& message);
    Message receiveMessage();

    void closeSocket();
};

#endif // SOCKET_H
