#include "Socket.h"
#include <iostream>

Socket::Socket(const qintptr socketDescriptor){
    this->setSocketDescriptor(socketDescriptor);
}

Socket::~Socket(){}

void Socket::sendMessage(const Message& message){
    this->write((message.m_name + ":" + message.m_text).data());
    this->flush();
}

Message Socket::receiveMessage(){
    std::string name, text;

    if(this->state() != QAbstractSocket::UnconnectedState && this->waitForReadyRead(500)){
        std::string message = this->readAll().constData();

        if(message.length() == 0){
            throw std::runtime_error("empty message");
        }

        const size_t pos = message.find(":");
        name = message.substr(0, pos);
        text = message.substr(pos + 1);
    }

    else{
        throw std::runtime_error("can't read message");
    }

    return Message{name, text};
}

void Socket::closeSocket(){
    this->close();
}
