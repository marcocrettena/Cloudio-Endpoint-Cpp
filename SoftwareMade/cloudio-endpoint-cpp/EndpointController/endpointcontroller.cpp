#include "endpointcontroller.h"

#include "EndpointStructure/endpoint.h"
#include "EndpointStructure/attribute.h"
#include "EndpointStructure/node.h"

STATE EndpointController::state = STATE::INIT;

EndpointController::EndpointController()
{
    this->endpoint=Cloudio_Endpoint::getInstance();
    this->msgToSend= new QueueMessage();
    this->msgReceived= new QueueMessage();
    this->mqtt=I_MQTT::getInstance();
    //Mutex aren't needed anymore as there is no more thread
    /*
    this->mutexMsgReceived = ResourceFactory::getInstance()->createMutex();
    this->mutexMsgToSend = ResourceFactory::getInstance()->createMutex();
    this->mutexThreadReceiver = ResourceFactory::getInstance()->createMutex();
    this->mutexState = ResourceFactory::getInstance()->createMutex();
    */
    //Creation of two Thread
    //Use of thread cancelled
    //The first thread will try to connect to the server. When it's successfull, he will send Data
    //The second thread listen to the cloud for request
    //this->threadSender = ResourceFactory::getInstance()->createThread(this, Thread::EntryMethodBody(&EndpointController::executeSend),"Sender");
    //this->threadReceiver = ResourceFactory::getInstance()->createThread(this, Thread::EntryMethodBody(&EndpointController::executeReading),"Reader");
}

EndpointController *EndpointController::getInstance()
{
    static EndpointController ec;
    return &ec;
}

void EndpointController::addNodeToCloud(Cloudio_Node *node)
{
    string topic = "@nodeAdded"+node->getTopic();
    json nodeInJSON = this->endpoint->nodeJSON(node);
    Message* newNode = new Message(topic, nodeInJSON.dump());
    this->msgToSend->push_front(newNode);
    this->executeSend();
}

void EndpointController::addNodeToCloud(string name)
{
    Cloudio_Node* node = this->endpoint->getNode(name);
    if(node!=nullptr){
        addNodeToCloud(node);
    }
    else{
        Log::printD("EndpointController::addNodeToCloud : fail to prevent the server, node not found");
    }
}

void EndpointController::removeNode(Cloudio_Node *node)
{
    string topic = "@nodeRemoved"+node->getTopic();
    string body = "";
    Message* rmvNode = new Message(topic,body);
    this->msgToSend->push_front(rmvNode);
    // DELETE NEXT LINE IF THREAD
    this->executeSend();
    this->endpoint->removeNode(node);
}

void EndpointController::removeNode(string name)
{
    Cloudio_Node* node = this->endpoint->getNode(name);
    if(node!=nullptr){
        removeNode(node);
    }
    else{
        Log::printD("EndpointController::removeNode : fail to delete the node, node not found");
    }
}

Cloudio_Endpoint *EndpointController::getEndpoint() const
{
    return endpoint;
}

void EndpointController::set_MQTT()
{
    /*      Not needed anymore with SSL Connection
    string host = FileManager::getInstance()->getHost();
    int pos = host.find_last_of(':');
    string hostname = host.substr(0,pos);
    int port = stoi(host.substr(pos+1));
    this->mqtt->setHostname(hostname);
    this->mqtt->setPort(port);
    */
    this->mqtt->setWillTopic("@offline/"+this->endpoint->getUuid());
    this->mqtt->setTransport();
}

void EndpointController::executeReading()
{
    //Get msg from list
    Message* msg = getMsgFromList(this->msgReceived);

    //Extract the topic and data
    string topic = msg->getTopic();
    string data = msg->getBody();
    int pos = topic.find('@');
    topic = topic.substr(pos,topic.length());
    //Iterator on topic
    list<string> temp = this->endpoint->parseTopic(topic);
    list<string>::iterator it = temp.begin();
    //Extract topic beginning with the endpoint uuid
    int pos2 = topic.find_first_of('/');
    string reduceTopic = topic.substr(pos2,topic.length());

    //Maybe we will have other command than set one day
    if((*it)=="@set"){
        it++;
        //Control the uuid maybe not efficient since our endpoint has only subscribe to the corresponding topic
        if(*it==this->endpoint->getUuid()){
            Cloudio_Attribute* attr = this->endpoint->getAttribute(reduceTopic);
            //Log::printD(data);
            json jTopic = json::parse(data);
            //Log::printD(jTopic.dump(4));
            if("Integer"==jTopic["type"]){
                attr->setValue(stoi(jTopic["value"].dump()));
            }
            else if("Number"==jTopic["type"]){
                attr->setValue((double)stod(jTopic["value"].dump()));
            }
            else if("String"==jTopic["type"]){
                attr->setValue(jTopic["value"].dump());
            }
            else if("Boolean"==jTopic["type"]){
                if(jTopic["value"].dump()=="true"){
                    attr->setValue(true);
                }
                if(jTopic["value"].dump()=="false"){
                    attr->setValue(false);
                }
            }
        }
    }
    delete msg;
}
    /*     TRY OF READING FUNCTION WITH A THREAD => it's hard to do this with some QObject like QMqttClient, there is certainly a way to do it with good patterns
     *      however, time is missing to search some informations and remake all the construction of the project.
    while(1){
        if(this->msgReceived.empty()){
            //Thread can sleep
            this->mutexThreadReceiver->lock();
            this->threadReceiver->stop();
            this->mutexThreadReceiver->unlock();
        }
        else {
            //Get msg from list
            this->mutexMsgReceived->lock();
            Message* msg = getMsgFromList(this->msgReceived);
            this->mutexMsgReceived->unlock();

            //Extract the topic and data
            string topic = msg->getTopic();
            string data = msg->getBody();
            int pos = topic.find('@');
            topic = topic.substr(pos,topic.length()-1);
            //Iterator on topic
            list<string> temp = this->endpoint->parseTopic(topic);
            list<string>::iterator it = temp.begin();
            //Extract topic beginning with the endpoint uuid
            int pos2 = topic.find_first_of('/');
            string reduceTopic = topic.substr(pos2,topic.length()-1);

            //Maybe we will have other command than set one day
            if((*it)=="@set"){
                it++;
                //Control the uuid maybe not efficient since our endpoint has only subscribe to the corresponding topic
                if(*it==this->endpoint->getUuid()){
                    Attribute* attr = this->endpoint->getAttribute(reduceTopic);
                    json jTopic = this->endpoint->attributeJSON(attr);
                    if("Integer"==jTopic["type"]){
                        attr->setValue(stoi(jTopic["value"].dump()));
                    }
                    if("Number"==jTopic["type"]){
                        attr->setValue((float)stod(jTopic["value"].dump()));
                    }
                    if("String"==jTopic["type"]){
                        attr->setValue(jTopic["value"].dump());
                    }
                    if("Boolean"==jTopic["type"]){
                        if(jTopic["value"]=="true"){
                            attr->setValue(true);
                        }
                        if(jTopic["value"]=="false"){
                            attr->setValue(false);
                        }
                    }
                }
            }
            delete msg;
        }
    }
}
*/

void EndpointController::executeSend()
{
    //Init useless but if one day we need a real state machine, it's already there at least
    if(state==STATE::INIT){
        state=STATE::OFFLINE;
    }
    if(state==STATE::OFFLINE){
        Log::printD("Try to connect with mqtt");
        this->mqtt->connectToHost();
    }
    if(state==STATE::ONLINE){
        this->endpoint->online=true;
        //Send birth message
        Message birth = birthMessage();
        this->mqtt->publish(birth.topic,birth.body,1,true);
        //Log::printD(birth.body);
        //Subscribe to "set" message
        string topic="@set/"+this->endpoint->getUuid()+"/#";
        this->mqtt->subscribe(topic);
        state=STATE::READY;
    }
    if(state==STATE::READY){
        while(!msgToSend->empty()){
            //List not empty so we send the message to the server and delete it
            Message* msg=getMsgFromList(this->msgToSend);
            this->mqtt->publish(msg->getTopic(),msg->getBody(),1,true);
            //Log::printD(msg->getBody());
            delete msg;
        }
    }
    /* FIRST TRY WITH A THREAD
     * See commentary on executeReading to understand what happens.
    while(1){
        if(state==STATE::INIT){
            state=STATE::OFFLINE;
        }
        if(state==STATE::OFFLINE){
            Log::printD("Try to connect with mqtt");
            this->mqtt->connectToHost();
            //TODO : Check list of msg, memorize them in a file or something else
        }
        if(state==STATE::ONLINE){
            //Send birth message
            Message birth = birthMessage();
            this->mqtt->publish(birth.topic,birth.body,1,true);
            Log::printD(birth.body);
            //Subscribe to "set" message
            string topic="@set/"+this->endpoint->getUuid()+"/#";
            this->mqtt->subscribe(topic);
            state=STATE::READY;
        }
        if(state==STATE::READY){
            this->mutexMsgToSend->lock();
            if(!msgToSend.empty()){
                Message* msg=getMsgFromList(this->msgToSend);
                //@update
                this->mqtt->publish(msg->getTopic(),msg->getBody(),1,true);
                delete msg;
            }
            this->mutexMsgToSend->unlock();
            this->threadSender->delay(1);

        }
    }
}*/
}

void EndpointController::onMessageReceived(string body, string topic)
{
    Message* msg = new Message(topic, body);
    this->msgReceived->push_front(msg);
    // DELETE FOLLOWING LINE IF THREAD
    this->executeReading();
    /*
    //If the main thread stop between the if and start(), it can causes a glitch in the programm, prevention of that with the mutex
    this->mutexThreadReceiver->lock();
    if(!this->threadReceiver->getIsRunning()){
        this->threadReceiver->start();
    }
    this->mutexThreadReceiver->unlock();
    */
}

void EndpointController::onConnect()
{
    this->state=STATE::ONLINE;
    Log::printD("Online!");
    // DELETE NEXT LINE IF NRF
    this->executeSend();
}

void EndpointController::onDisconnect()
{
    this->state=STATE::OFFLINE;
    //Finally, the attribute online isn't used. LastWill and birthMessage make that without this attribute
    this->endpoint->online=false;
    // DELETE NEXT LINE IF NRF
    this->executeSend();
}

Message EndpointController::birthMessage()
{
    string body = this->endpoint->makeJSON_DataModel().dump(4);
    string topic = "@online/"+this->endpoint->getUuid();
    Message retVal = Message(topic,body);
    return retVal;
}

Message* EndpointController::getMsgFromList(list<Message*> listToCheck)
{
    Message* msg = listToCheck.front();
    string topic = msg->getTopic();
    string data = msg->getBody();
    Message* retVal =new Message(topic,data);
    //Delete the message from the list correctly, avoid the leak memory
    listToCheck.pop_front();
    delete msg;
    return retVal;
}

Message *EndpointController::getMsgFromList(QueueMessage* listToCheck)
{
    Message* msg = listToCheck->front();
    string topic = msg->getTopic();
    string data = msg->getBody();
    Message* retVal =new Message(topic,data);
    //Delete the message from the list correctly, avoid the leak memory
    listToCheck->pop_front();
    delete msg;
    return retVal;
}

list<string> EndpointController::parseTopic(string topic)
{
    //The endpoint had already the function to do that so no need to reimplement
    return this->endpoint->parseTopic(topic);
}

void EndpointController::run()
{
    this->endpoint->makeJSON();
    set_MQTT();

    //To try with thread, uncomment the start() methods and comment lines after
    //Thread wasn't a success for this project as I wasn't aware of the
    //difficulties some QObjects can be to manipulate.
    //Not enough time to search and follow a good pattern to use simultaneously both.

    //this->threadSender->start();
    //this->threadReceiver->start();

    //Solution without thread : do that and the onConnect() method will launch the executeSend method one time
    if(state==STATE::INIT){
        state=STATE::OFFLINE;
    }
    if(state==STATE::OFFLINE){
        Log::printD("Try to connect with mqtt");
        this->mqtt->connectToHost();
    }
}

void EndpointController::setAttributeValue(AttributeInt *attribute, int value)
{
    attribute->changeValue(value);
    string topic = "@update"+attribute->getTopic();
    //Log::printD(topic);
    string data = this->endpoint->attributeJSON(attribute).dump(4);
    Message* msg = new Message(topic,data);
    //this->mutexMsgToSend->lock();
    this->msgToSend->push_front(msg);
    //this->mutexMsgToSend->lock();
    // DELETE NEXT LINE IF NRF
    this->executeSend();
}

void EndpointController::setAttributeValue(AttributeDouble *attribute, float value)
{
    attribute->changeValue(value);
    string topic = "@update"+attribute->getTopic();
    //Log::printD(topic);
    string data = this->endpoint->attributeJSON(attribute).dump(4);
    Message* msg = new Message(topic,data);
    //this->mutexMsgToSend->lock();
    this->msgToSend->push_front(msg);
    //this->mutexMsgToSend->lock();
    // DELETE NEXT LINE IF NRF
    this->executeSend();
}

void EndpointController::setAttributeValue(AttributeBool *attribute, bool value)
{
    attribute->changeValue(value);
    string topic = "@update"+attribute->getTopic();
    string data = this->endpoint->attributeJSON(attribute).dump(4);
    Message* msg = new Message(topic,data);
    //this->mutexMsgToSend->lock();
    this->msgToSend->push_front(msg);
    //this->mutexMsgToSend->lock();
    // DELETE NEXT LINE IF NRF
    this->executeSend();
}

void EndpointController::setAttributeValue(AttributeString *attribute, string value)
{
    attribute->changeValue(value);
    string topic = "@update"+attribute->getTopic();
    //Log::printD(topic);
    string data = this->endpoint->attributeJSON(attribute).dump(4);
    Message* msg = new Message(topic,data);
    //this->mutexMsgToSend->lock();
    this->msgToSend->push_front(msg);
    //this->mutexMsgToSend->lock();
    // DELETE NEXT LINE IF NRF
    this->executeSend();
}
