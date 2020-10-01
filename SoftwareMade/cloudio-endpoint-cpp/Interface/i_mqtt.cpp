#include "i_mqtt.h"
#include "EndpointController/endpointcontroller.h"

void I_MQTT::onMessageReceived(string message, string topic)
{
    EndpointController::getInstance()->onMessageReceived(message, topic);
}

void I_MQTT::onDisconnect()
{
    EndpointController::getInstance()->onDisconnect();
}

void I_MQTT::onConnect()
{
    EndpointController::getInstance()->onConnect();
}

