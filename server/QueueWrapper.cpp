 #include "QueueWrapper.h"

QueueWrapper::QueueWrapper(){

}

int QueueWrapper::getUserSize(){
    //std::lock_guard<std::mutex> lk(this->mutex);
    return this->users.size();
}

void QueueWrapper::setUser(QTcpSocket* socket){
    std::lock_guard<std::mutex> lk(this->mutex);
    this->users.push_back(socket);
}

QTcpSocket* QueueWrapper::getUser(int index){
    //std::lock_guard<std::mutex> lk(this->mutex);
    if(index == -1){
        return this->users.back();
    }
    else{
        return this->users[index];
    }
}

void QueueWrapper::removeUser(int index){
    //std::lock_guard<std::mutex> lk(this->mutex);
    if(index == -1){
        this->users.pop_back();
    }
    else{
        this->users.erase(this->users.begin() + index);
    }
}
