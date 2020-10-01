#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
using namespace std;

class EndpointController;
class QueueMessage;
/**
 * @brief The Message class
 * Our MQTTS message will be abstract in these messages composed by a topic and a body, both in string element
 */
class Message
{
    friend EndpointController;
    friend QueueMessage;

private:
    Message(string topic, string body);
    string getTopic() const;
    void setTopic(const string &value);

    string getBody() const;
    void setBody(const string &value);

private:
    string topic;
    string body;
};

#endif // MESSAGE_H
