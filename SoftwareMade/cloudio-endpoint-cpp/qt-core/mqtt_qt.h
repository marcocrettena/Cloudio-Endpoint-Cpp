#ifndef MQTT_H
#define MQTT_H

#include "Interface/i_mqtt.h"
#include "ssl_qt.h"
#include "resourcefactory.h"
#include "Interface/i_logger.h"

#include <QtMqtt/QtMqtt>
#include <QObject>
#include <QtPlugin>

class MQTT_qt : public QObject, public I_MQTT
{
    Q_OBJECT
    Q_INTERFACES(I_MQTT)
public:
    MQTT_qt();
    static MQTT_qt* getInstance();
private:
    QMqttClient* qmc;
    static MQTT_qt* mqtt_qt;
    SSL_qt* ssl;
    Mutex* mutex;
    // I_MQTT interface
public:
    virtual ~MQTT_qt(){}
    void setHostname(string name);
    void setPort(int port);
    void subscribe(string topic);
    void publish(string topic, string data, int qos, bool retain);
    void close();
    bool isConnected();
    void connectToHost();
    void setWillTopic(string topic);
    void setTransport();
public slots:
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void onConnected();
    void onDisconnected();
};

#endif // MQTT_H
