#ifndef SERVER_H
#define SERVER_H

#include <QueueWrapper.h>

class Server : public QTcpServer{
public:
    Server();
    ~Server();

    void start();

    void incomingConnection(qintptr socketDescriptor) override;

    void handshake(qintptr socketDescriptor);
    void handshakeResponse(QTcpSocket* socket);

    void communication();

    void closeConnection(QTcpSocket* socket);

    void writeResponse();
    bool writeLog(QTcpSocket* socket);

    QTcpSocket* getUser();

private:
    QTcpSocket* socket;
    std::thread communication_thread, connection_thread;
    bool isCommunicate = false;
    QueueWrapper users;
    //std::vector<QTcpSocket*> users;
};
#endif // SERVER_H
