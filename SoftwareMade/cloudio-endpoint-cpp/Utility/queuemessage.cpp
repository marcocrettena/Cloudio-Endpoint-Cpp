#include "queuemessage.h"
#include "message.h"

QueueMessage::QueueMessage()
{

}

void QueueMessage::push_front(Message *msg)
{
    map<string,int>::iterator itMap =this->counterTopic.begin();
    itMap = this->counterTopic.find(msg->getTopic());
    if(itMap == counterTopic.end()){
        //Add new topic message in the map
        counterTopic[msg->getTopic()]=1;
    }
    else{
        //Increase counter of message for the specific topic
        if(itMap->second < MaxMemorize){
            itMap->second = itMap->second+1;
        }
        //Need to delete the more ancient Message
        else{
            list<Message*>::iterator it = this->queueMessage.begin();
            list<Message*>::iterator itOnLastMessage = this->queueMessage.begin();

            for(it;it!=queueMessage.end();it++){
                if((*it)->getTopic()==msg->getTopic()){
                    itOnLastMessage=it;
                }
            }
            delete (*itOnLastMessage);
            queueMessage.erase(itOnLastMessage);
        }
    }
    //Add message in the list
    this->queueMessage.push_front(msg);
}

Message *QueueMessage::front()
{
    return this->queueMessage.front();
}

void QueueMessage::pop_front()
{
    string topic = this->queueMessage.front()->getTopic();
    map<string,int>::iterator itMap =this->counterTopic.begin();
    itMap = this->counterTopic.find(topic);
    if(itMap!=counterTopic.end()){
        //decrease counter
        if(itMap->second != 1){
            itMap->second = itMap->second-1;
        }
        //No message with this specific topic anymore
        else{
            counterTopic.erase(itMap);
        }
    }
    queueMessage.pop_front();
}

bool QueueMessage::empty()
{
    return this->queueMessage.empty();
}
