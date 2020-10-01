#include "mqtt_qt.h"
#include "Interface/i_filemanager.h"

MQTT_qt* MQTT_qt::mqtt_qt = nullptr;

MQTT_qt::MQTT_qt()
{
    qmc= new QMqttClient();
    ssl = SSL_qt::getInstance();
    QObject::connect(qmc,&QMqttClient::messageReceived,this,&MQTT_qt::onMessageReceived);
    QObject::connect(qmc,&QMqttClient::connected,this,&MQTT_qt::onConnected);
    QObject::connect(qmc,&QMqttClient::disconnected,this,&MQTT_qt::onDisconnected);
    mutex = ResourceFactory::getInstance()->createMutex();
}

I_MQTT *I_MQTT::getInstance(){
    return MQTT_qt::getInstance();
}

MQTT_qt *MQTT_qt::getInstance()
{
    if(mqtt_qt==nullptr){
        mqtt_qt = new MQTT_qt();
    }
    return mqtt_qt;
}

void MQTT_qt::setHostname(string name)
{
    const QString qName = QString::fromStdString(name);
    mutex->lock();
    this->qmc->setHostname(qName);
    mutex->unlock();
}

void MQTT_qt::setPort(int port)
{
    mutex->lock();
    this->qmc->setPort(port);
    mutex->unlock();
}

void MQTT_qt::subscribe(string topic)
{
    //QMqttTopicFilter topic2{"test/#"};
    QMqttTopicFilter topicFilter = QMqttTopicFilter(QString::fromStdString(topic));
    mutex->lock();
    this->qmc->subscribe(topicFilter);
    mutex->unlock();
}

void MQTT_qt::publish(string topic, string data, int qos=0, bool retain=false)
{
    QMqttTopicName topicName = QMqttTopicName(QString::fromStdString(topic));
    QByteArray byteData(data.c_str(),data.length());
    mutex->lock();
    this->qmc->publish(topicName,byteData,qos,retain);
    mutex->unlock();
}

void MQTT_qt::close()
{
    mutex->lock();
    this->qmc->disconnectFromHost();
    mutex->unlock();
}

bool MQTT_qt::isConnected()
{
    mutex->lock();
    if(this->qmc->state()==QMqttClient::ClientState::Connected){
        return true;
    }
    else {
        return false;
    }
    mutex->unlock();
}

void MQTT_qt::connectToHost()
{
    mutex->lock();
    if(qmc->state()!=QMqttClient::Connecting){
        qmc->connectToHost();
    }
    else{
        Log::printD("Already connecting");
    }
    mutex->unlock();
}

void MQTT_qt::setWillTopic(string topic)
{
    QByteArray topicArray = QByteArray(topic.c_str(), topic.length());
    qmc->setWillTopic(topicArray);
}

void MQTT_qt::setTransport()
{
    mutex->lock();
    this->qmc->setTransport(ssl->getSocket(), QMqttClient::AbstractSocket);
    mutex->unlock();
}

void MQTT_qt::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    I_MQTT::onMessageReceived(message.toStdString(),topic.name().toStdString());
}

void MQTT_qt::onConnected()
{
    I_MQTT::onConnect();
}

void MQTT_qt::onDisconnected()
{
    I_MQTT::onDisconnect();
}

