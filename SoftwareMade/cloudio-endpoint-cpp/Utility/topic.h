#ifndef TOPIC_H
#define TOPIC_H

#include <iostream>

class Cloudio_Endpoint;
class Cloudio_Node;
class Cloudio_Object;
class Cloudio_Attribute;

using namespace std;
/**
 * @brief The Uuid class
 * More like the "Topic class", this class provides method to find what will be the topic of an attribute, object or node.
 */
class Topic
{
private:
    friend Cloudio_Endpoint;
    friend Cloudio_Node;
    friend Cloudio_Object;
    friend Cloudio_Attribute;

    static string setTopic(Cloudio_Attribute* attribute);
    static string setTopic(Cloudio_Object* object);
    static string setTopic(Cloudio_Node* node);
    static bool hasSpecialChar(string name);
private:
    Topic();
};

#endif // TOPIC
