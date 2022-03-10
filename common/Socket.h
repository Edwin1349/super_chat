#ifndef SOCKET_H
#define SOCKET_H

#include "Message.h"
#include <QTcpSocket>

class Socket : public QTcpSocket{
public:
    Socket(qintptr socketDescriptor);
    ~Socket();

    void sendMassage(Message message);
    Message receiveMessage();

    void closeSocket();
};

#endif // SOCKET_H
