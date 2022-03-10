#include "Socket.h"

Socket::Socket(qintptr socketDescriptor){
    this->setSocketDescriptor(socketDescriptor);
}

Socket::~Socket(){}

void Socket::sendMassage(Message message){
    this->write((message.m_name + ":" + message.m_text).data());
    this->flush();
    this->waitForBytesWritten(500);
}

Message Socket::receiveMessage(){
    std::string m_name, m_text;

    if(this->state() != QAbstractSocket::UnconnectedState && this->waitForReadyRead(500)){
        std::string s_message = this->readAll().constData();

        int pos = s_message.find(":");
        m_name = s_message.substr(0, pos);
        s_message.erase(0, pos + 1);

        m_text = s_message;
    }

    return Message{m_name, m_text};
}

void Socket::closeSocket(){
    this->close();
}
