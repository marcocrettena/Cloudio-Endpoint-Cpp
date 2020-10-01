#ifndef ENDPOINTFACTORY_H
#define ENDPOINTFACTORY_H

#include <iostream>

#include "EndpointStructure/attribute.h"
class Cloudio_Endpoint;
class Cloudio_Node;
class Cloudio_Object;

using namespace std;

/**
 * @brief The EndpointFactory class
 * Class who provides method to create an Endpoint with their nodes, objects and attribute.
 * This class prevent the user to make misunderstanding construction or unplanned methodology to build his endpoint.
 */
class EndpointFactory
{
public:
    /**
     * @brief getInstance
     * Method to get the unique instance of the class (singleton)
     * @return the unique instance of this class
     */
    static EndpointFactory* getInstance();
    /**
     * @brief addNode
     * Create and add a node to the endpoint
     * @param name : name of the endpoint, usefull for the topic
     * @return The created node
     */
    Cloudio_Node* addNode(string name);
    /**
     * @brief removeNode
     * Search the node with the good name and remove it from the endpoint
     * @param name : name of the node
     */
    void removeNode(string name);
    /**
     * @brief removeNode
     * Remove the node
     * @param node : node to be removed
     */
    void removeNode(Cloudio_Node* node);
    /**
     * @brief addObject
     * Create and add an object to the endpoint
     * @param parent : Node that possess the object
     * @param name : Name of the Object
     * @return The created Object
     */
    Cloudio_Object* addObject(Cloudio_Node* parent, string name);
    /**
     * @brief addObject
     * Create and add an object to the endpoint
     * @param parent : Object that possess the Object
     * @param name : name of the created Object
     * @return The created Object
     */
    Cloudio_Object* addObject(Cloudio_Object* parent, string name);
    /**
     * @brief addAttribute
     * Create and add an attribute to the endpoint
     * @param parent : Object who possess the attribute
     * @param name : name of the attribute
     * @param constraint : constraint of the attribute
     * @param initValue : initial value of the attribute
     * @return The attribute created
     */
    AttributeInt* addAttribute(Cloudio_Object* parent, string name, Constraint constraint, int initValue, void (*callback)(int));
    AttributeString* addAttribute(Cloudio_Object* parent, string name, Constraint constraint, string initValue, void (*callback)(string));
    AttributeDouble* addAttribute(Cloudio_Object* parent, string name, Constraint constraint, double initValue, void (*callback)(double));
    AttributeBool* addAttribute(Cloudio_Object* parent, string name, Constraint constraint, bool initValue, void (*callback)(bool));
    AttributeInt* addAttribute(Cloudio_Object* parent, string name, Constraint constraint, int initValue);
    AttributeString* addAttribute(Cloudio_Object* parent, string name, Constraint constraint, string initValue);
    AttributeDouble* addAttribute(Cloudio_Object* parent, string name, Constraint constraint, double initValue);
    AttributeBool* addAttribute(Cloudio_Object* parent, string name, Constraint constraint, bool initValue);
private:
    Cloudio_Endpoint* endpoint;         ///Unique instance of the endpoint
private:
    /**
     * @brief EndpointFactory
     * Simple constructor as this class is a singleton
     */
    EndpointFactory();

};

#endif // ENDPOINTFACTORY_H
