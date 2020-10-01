#ifndef NODE_H
#define NODE_H

#include <list>
#include <iostream>

#include "object.h"

using namespace std;

class Cloudio_Endpoint;
class EndpointFactory;
class EndpointController;

/**
 * @brief The Node class
 * A node is like a full system, he will posses all the objects needed for a particular system, or
 * at least, this is what I expect that to be.
 */
class Cloudio_Node
{
    friend Cloudio_Endpoint;
    friend Topic;
    friend EndpointFactory;
    friend EndpointController;
private:
    Cloudio_Node(string name);
    ~Cloudio_Node();
    Cloudio_Object* getObject(string name);
    void addObject(Cloudio_Object* object);
    void removeObject(Cloudio_Object* object);
    Cloudio_Endpoint* getParent();
    string getName();
    void displayTopic();
    string getTopic() const;
private:
    void setParent(Cloudio_Endpoint* endpoint);
private:
    list<Cloudio_Object*> objects;              ///List of objects in the Node
    string name;                                ///Name of the Node
    Cloudio_Endpoint* parent;                   ///Pointer on the unique Cloudio_Endpoint
    string topic;                               ///Specific topic of the Node
};

#endif // NODE_H
