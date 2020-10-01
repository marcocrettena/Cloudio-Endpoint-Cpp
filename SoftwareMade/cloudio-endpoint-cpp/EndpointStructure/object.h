#ifndef OBJECT_H
#define OBJECT_H

#include <list>
#include <iostream>

#include "attribute.h"

using namespace std;

class Cloudio_Node;
class Cloudio_Endpoint;
class EndpointFactory;
/**
 * @brief The Cloudio_Object class
 * An Object is a part of the system, he can have the attributes or other sub-object, for example
 * he can possess a setPoint for the Temperature and a captor (the sub-object) which will provide the measured temperature.
 */
class Cloudio_Object
{
    friend Cloudio_Node;
    friend Cloudio_Endpoint;
    friend Topic;
    friend EndpointFactory;
private:
    Cloudio_Object(string name);
    ~Cloudio_Object();
    Cloudio_Object* getObject(string name);
    Cloudio_Attribute* getAttribute(string name);
    void addObject(Cloudio_Object* object);
    void addAttribute(Cloudio_Attribute* attribute);
    void removeObject(Cloudio_Object* object);
    void removeAttribute(Cloudio_Attribute* attribute);
    Cloudio_Object* getParentObject();
    Cloudio_Node* getParentNode();
    string getName();
    void displayTopic();
    string getTopic() const;

private:
    void setParent(Cloudio_Object* object);
    void setParent(Cloudio_Node* node);
private:
    list<Cloudio_Object*> objects;              ///List of objects
    list<Cloudio_Attribute*> attributes;        ///List of attributes
    Cloudio_Object* parentObject;               ///The parent can be an Object
    Cloudio_Node* parentNode;                   ///The parent can be a Node
    string name;                                ///Name of this Object
    string topic;                               ///Specific topic of this Object
};

#endif // OBJECT_H
