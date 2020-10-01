#ifndef ENDPOINTCONTROLLER_H
#define ENDPOINTCONTROLLER_H



#include "Interface/i_logger.h"
#include "Interface/resourcefactory.h"
#include "Interface/i_filemanager.h"
#include "Interface/i_mqtt.h"

#include "Utility/message.h"
#include "Utility/queuemessage.h"

#include <list>

/**
 * @brief The STATE enum
 * This enum is used to retained what the current state of the connection is
 * So if we aren't offline, attributes changes will be sent to the broker, otherwise we need to store it
 */
enum STATE{
    INIT,
    ONLINE,
    READY,
    OFFLINE
};

class Cloudio_Endpoint;
class Cloudio_Node;
class AttributeInt;
class AttributeDouble;
class AttributeBool;
class AttributeString;

/**
 * @brief The EndpointController class
 * This class contains two threads who will make the communication with the cloud.io server (receiver and sender)
 * This class is a singleton, the user will use the run() method after the Endpoint is fully created and send() method
 * to tell that an attribute value has changed.
 */
/* A lot of things have happend late in the class :
 * Thread were abandonned as the QMqttClient is a QObject class
 * A QObject with Thread need some works to do as normally QObject can replace the role of Threads
 * By following a pattern, it's certainly possible to find a good structure for this project.
 */
class EndpointController : public ThreadEntryPointProvider
{
    friend I_MQTT;
public:
    /**
     * @brief getInstance
     * Method to get the unique instance of this class (singleton)
     * @return the unique instance of the class
     */
    static EndpointController* getInstance();
    /**
     * @brief addNode
     * Method to signify to the server that a new Node is added to the endpoint with their information
     * This is important to call this method only
     * after the birth message is sent (otherwise it's useless to call this method)
     * @param node who is added and newly used in the endpoint
     */
    void addNodeToCloud(Cloudio_Node* node);
    void addNodeToCloud(string name);
    /**
     * @brief removeNode
     * Method to delete the structure of the node in the server and in the application
     * it's useless to call this method before the birth message is sent.
     * @param node to delete from the endpoint
     */
    void removeNode(Cloudio_Node* node);
    void removeNode(string name);
    /**
     * @brief run
     * Start the application, should be called after the complete creation of the endpoint
     */
    void run();
    //Methods for the user to change the value of our attribute
    void setAttributeValue(AttributeInt* attribute, int value);
    void setAttributeValue(AttributeDouble* attribute, float value);
    void setAttributeValue(AttributeBool* attribute, bool value);
    void setAttributeValue(AttributeString* attribute, string value);

private:

    static STATE state;                 ///Current state of the application
    STATE oldstate;                     ///Ancient state of the application (in case if it's needed, well there is no state machine for the moment so useless)

    Cloudio_Endpoint* endpoint;         ///Unique endpoint instance of the program (singleton)

    Thread* threadReceiver;             ///Thread that will check the message received from the broker
    Thread* threadSender;               ///Thread that will check the message to send to the broker, he verifies the state of the application too

    I_MQTT* mqtt;                       ///Instance that will contain all the method we need to do a mqtt connection/communication

    QueueMessage* msgReceived;         ///Queue of received messages
    QueueMessage* msgToSend;           ///Queue of messages to send

    Mutex* mutexMsgReceived;            ///To not have two threads who access to the list msgReceived at the same time
    Mutex* mutexMsgToSend;              ///To not have two threads who access to the list msgToSend at the same time
    Mutex* mutexThreadReceiver;         ///To not have two threads who modifies the status of threadReceiver (see bool isRunning)
    Mutex* mutexState;                  ///To not have two threads who modifies the state of the application on the same time

private:
    /**
     * @brief EndpointController
     * Singleton class implies simple constructor
     */
    EndpointController();
    Cloudio_Endpoint *getEndpoint() const;
    /**
     * @brief set_MQTT
     * method to set all the parameters our mqttClient need
     */
    void set_MQTT();
    /**
     * @brief executeReading
     * threadReading will execute this method
     */
    void executeReading();
    /**
     * @brief executeSend
     * threadSender will execute this method
     */
    void executeSend();
    /**
     * @brief onMessageReceived
     * Put the received message in the msgReceived queue
     * @param body: data of the message
     * @param topic: topic of the message
     */
    void onMessageReceived(string body, string topic);
    /**
     * @brief onConnect
     * When we are connected, change the state of the application
     */
    void onConnect();
    /**
     * @brief onDisconnect
     * When we are disconnected, change the state of the application
     */
    void onDisconnect();
    /**
     * @brief birthMessage
     * @return birth message to send to the broker
     */
    Message birthMessage();

    /**
     * @brief getMsgFromList
     * Get the next message on the list to treat and free the memory allocation
     * @param listToCheck
     * @return Message to treat next
     */
    Message* getMsgFromList(list<Message*> listToCheck);
    Message* getMsgFromList(QueueMessage* listToCheck);
    /**
     * @brief parseTopic
     * From a topic, separate the different elements (like the command, the uuid, the node, etc...)
     * @param topic : topic to be parsed
     * @return List of string of the different elements name
     */
    list<string> parseTopic(string topic);
};

#endif // ENDPOINTCONTROLLER_H
