#ifndef I_MQTT_H
#define I_MQTT_H

#include <iostream>
#include <QtPlugin>

//IF NOT QT, PUT 0
#define QT_PROJECT 1

using namespace std;

class EndpointController;

/**
 * @brief The I_MQTT class
 * This class is used to permit the endpointController to call the important method to do a MQTT communication.
 * The implementation depends of the environnement, so this is an abstraction layer.
 */
class I_MQTT
{
    friend EndpointController;
protected:
    static I_MQTT * getInstance();
protected:
    virtual ~I_MQTT() = default;
    virtual void setHostname(string name)=0;
    virtual void setPort(int port)=0;
    virtual void subscribe(string topic)=0;
    virtual void publish(string topic, string data,int qos=0, bool retain=false)=0;
    virtual void close()=0;
    virtual bool isConnected()=0;
    virtual void connectToHost()=0;
    virtual void setWillTopic(string topic)=0;
    virtual void setTransport()=0;

    //Function usefull to call methods of the EndpointController, they are callback for a mqttClient instance
    void onMessageReceived(string message, string topic);
    void onDisconnect();
    void onConnect();

protected:
    I_MQTT()=default;
};
#if QT_PROJECT
Q_DECLARE_INTERFACE(I_MQTT,"MqttInterface")
#endif

#endif // I_MQTT_H
