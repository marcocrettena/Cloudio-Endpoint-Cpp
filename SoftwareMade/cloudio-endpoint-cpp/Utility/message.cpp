#include "message.h"

Message::Message(string topic, string body)
{
    this->topic = topic;
    this->body = body;
}

string Message::getTopic() const
{
    return topic;
}

void Message::setTopic(const string &value)
{
    topic = value;
}

string Message::getBody() const
{
    return body;
}

void Message::setBody(const string &value)
{
    body = value;
}
