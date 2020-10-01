#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <list>
#include <iostream>

#include "node.h"
#include "Utility/topic.h"
#include "Utility/json.hpp"

#include "Interface/i_mqtt.h"
#include "Interface/i_os.h"
#include "Interface/i_filemanager.h"

#include "EndpointController/endpointcontroller.h"

using json = nlohmann::json;

using namespace std;

class EndpointController;
class EndpointFactory;
class Topic;

/**
 * @brief The Endpoint class
 * The endpoint contains all systems (nodes) that he must send the informations in Cloud.io
 */
class Cloudio_Endpoint
{
    friend EndpointController;
    friend EndpointFactory;
    friend Topic;

private:
    list<Cloudio_Node*> nodes;          ///List of Cloudio_Node that the Endpoint possesses
    string uuid;                        ///Unique identifier given by the server
    bool online;                        ///Status of the connection with the server
    json j;                             ///Structure of the endpoint in a json format
private:
    Cloudio_Endpoint();
    ~Cloudio_Endpoint();
    /**
     * @brief addNode
     * Add a Node to the endpoint
     * @param node to add
     */
    void addNode(Cloudio_Node* node);
    /**
     * @brief removeNode
     * Remove the node from the list
     * @param node to be deleted
     */
    void removeNode(Cloudio_Node* node);
    /**
     * @brief getNode
     * Find the Node in the list with the name given
     * @param name, name of the Cloudio_Node
     * @return Node with the given name, nullptr if not found
     */
    Cloudio_Node* getNode(string name);
    string getUuid();
    /**
     * @brief displayUuid
     * Display the uuid in the console
     */
    void displayUuid();
    static Cloudio_Endpoint* getInstance();
    json getJSON() const;
    /**
     * @brief makeJSON
     * Make the complete JSON structure of the Endpoint
     */
    void makeJSON();
    /**
     * @brief makeJSON_DataModel
     * Correct structure to be sent for the birthMessage
     * @return the json to be sent for birthMessage
     */
    json makeJSON_DataModel();
    /**
     * @brief attributeJSON
     * Method to put an Attribute into JSON format
     * @param attribute to be in JSON format
     * @return the json object of the Attribute
     */
    json attributeJSON(Cloudio_Attribute* attribute);
    /**
     * @brief objectJSON
     * Method to put an Object into JSON format
     * @param object to be in JSON format
     * @return the json object of the Object
     */
    json objectJSON(Cloudio_Object* object);
    /**
     * @brief nodeJSON
     * Method to put a Node into JSON format
     * @param node to be in JSON format
     * @return the json object of the Node
     */
    json nodeJSON(Cloudio_Node* node);
    /**
     * @brief parseTopic
     * the topic is several instances separated with a "/", this function permits to retrieve the name of the instances
     * with the list of names, we can so retrieve the different instances of different objects types in the arborescence of the Endpoint
     * @param topic
     * @return list of strings with the different name of instances
     */
    list<string> parseTopic(string topic);
    /**
     * @brief getObject
     * Get the object in the arborescence in the Endpoint with the topic
     * @param topic
     * @return The wanted Object
     */
    Cloudio_Object* getObject(string topic);
    /**
     * @brief getAttribute
     * Get the attribute in the arborescence in the Endpoint with the topic
     * @param topic
     * @return The wanted Attribute
     */
    Cloudio_Attribute* getAttribute(string topic);
};

#endif // ENDPOINT_H
