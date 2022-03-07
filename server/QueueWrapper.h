#ifndef QUEUEWRAPPER_H
#define QUEUEWRAPPER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <QString>


class QueueWrapper{
public:
    QueueWrapper();

    void setUser(QTcpSocket* socket);
    QTcpSocket* getUser(int index = -1);
    void removeUser(int index = -1);

    int getUserSize();

    std::mutex mutex;
private:

    std::vector<QTcpSocket*> users;
};

#endif // QUEUEWRAPPER_H
