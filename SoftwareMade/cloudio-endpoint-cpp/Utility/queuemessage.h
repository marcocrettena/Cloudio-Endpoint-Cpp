#ifndef QUEUEMESSAGE_H
#define QUEUEMESSAGE_H

#include "queuemessage.h"

#include <list>
#include <map>

#include <iostream>
using namespace std;

//Number of Messages to send at the cloud for a specific attribute : can't be more than MaxMemorize
#define MaxMemorize 5

class Message;
class EndpointController;
/**
 * @brief The QueueMessage class
 * This class is used to contain a list of Message. It will one day implement some options
 * for the user to choose options for the list of message to send : how many messages of a specific attribute
 * it will memorize, should the list keep a trace of the average of the deleted values? (Some works will be
 * needed for that since an AttributeString will not have an average (so type of attribute to check)
 */
class QueueMessage
{
    friend EndpointController;
private:
    QueueMessage();
private:
    list<Message*> queueMessage;            ///Our list of messages
    map<string,int> counterTopic;           ///possess the count the number of messages for a specific topic
private:
    //These functions will do almost the same a normal std::list except it checks the MaxMemorize value
    void push_front(Message* msg);
    Message* front();
    void pop_front();
    bool empty();
};

#endif // QUEUEMESSAGE_H
