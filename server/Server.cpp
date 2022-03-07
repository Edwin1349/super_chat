#include <Server.h>

Server::Server(){
    communication_thread = std::thread(&Server::writeResponse, this);
    communication_thread.detach();
}

Server::~Server(){}

void Server::start(){
    if(!this->listen(QHostAddress::Any, 1234)){
        std::cout << "Server could not start!" << std::endl;
    }
    else{
        std::cout << "Server started!" << std::endl;
    }
}

void Server::incomingConnection(qintptr socketDescriptor){
    connection_thread = std::thread(&Server::handshake, this, socketDescriptor);
    connection_thread.join();
}

void Server::handshake(qintptr socketDescriptor){
    this->socket = new QTcpSocket;
    this->socket->setSocketDescriptor(socketDescriptor);
    //this->addPendingConnection(socket);
    handshakeResponse(socket);
    users.setUser(socket);
}

void Server::handshakeResponse(QTcpSocket *socket){
    std::cout<< socket << " Connected!"<<std::endl;

    //socket->write("hello from server\n");
    socket->flush();
    socket->waitForBytesWritten(1000);
}


void Server::writeResponse(){
    forever{
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        users.mutex.lock();
        for(int i = 0; i < users.getUserSize(); i++){

            if(users.getUser(i)->state() == QAbstractSocket::UnconnectedState){
                std::cout << users.getUser(i) << " Disconnected!" << std::endl;
                users.getUser(i)->close();
                users.removeUser(i);
            }
            if(users.getUser(i)->state() != QAbstractSocket::UnconnectedState && users.getUser(i)->waitForReadyRead(500)){
                std::cout << "Write!" << std::endl;
                QByteArray array = this->users.getUser(i)->readAll();
                qDebug() << array;
                for(int j = 0; j < users.getUserSize(); j++){
                    users.getUser(j)->write(array);
                    users.getUser(j)->flush();
                    users.getUser(j)->waitForBytesWritten(500);
                }
            }

        }
        users.mutex.unlock();
    }
}



bool Server::writeLog(QTcpSocket *socket){
    std::ofstream logfile;
    logfile.open("server.log", std::ios::out | std::ios::app | std::ios::binary);

    if(!logfile.is_open()){
        return false;
    }

    char buffer[256];
    while(true){
        int size = socket->read(buffer, 256);
        logfile.write(buffer, size);

        if (size == 0 && !socket->waitForReadyRead(300)){
            break;
        }
    }
    logfile.write("\n\n", 2);

    logfile.close();

    return true;
}
