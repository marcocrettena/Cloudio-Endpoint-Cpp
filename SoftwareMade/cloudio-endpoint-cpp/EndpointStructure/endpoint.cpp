#include "endpoint.h"

Cloudio_Endpoint::Cloudio_Endpoint()
{
    this->uuid=I_FileManager::getInstance()->getUuid();
    this->online=false;
}

Cloudio_Endpoint::~Cloudio_Endpoint()
{
    for(list<Cloudio_Node*>::iterator it=nodes.begin() ; it!=nodes.end();){
        delete *it;
        it=nodes.erase(it);
    }
}

void Cloudio_Endpoint::addNode(Cloudio_Node *node)
{
    bool errorName=false;
    //Check if the name hasn't special character
    errorName = Topic::hasSpecialChar(node->getName());
    //Check if the name isn't already taken
    if(errorName==false){
        for(list<Cloudio_Node *>::iterator it = nodes.begin(); it!=nodes.end() && errorName==false;it++){
            if((*it)->name==node->name){
                errorName=true;
                Log::printD("Endpoint::addNode : Name of Node already taken in this Endpoint!");
            }
        }
    }
    else{
        Log::printD("Endpoint::addNode : Name of Node possess a special character");
    }
    if(errorName==false){
        if(node->parent==nullptr){
            nodes.push_front(node);
            node->setParent(this);
            node->topic=Topic::setTopic(node);
        }
    }
}

void Cloudio_Endpoint::removeNode(Cloudio_Node *node)
{
    bool foundName=false;
    for(list<Cloudio_Node *>::iterator it = nodes.begin(); it!=nodes.end() && foundName==false;it++){
        if((*it)->name==node->name){
            foundName=true;
            delete *it;
            nodes.erase(it);
        }
    }
    if(foundName==true){
        //Logger::getInstance()->logPrint("Endpoint::removeNode : Object deleted");
    }
    else {
        I_Logger::getInstance()->logPrint("Endpoint::removeNode : Object not found");
    }
}

Cloudio_Node* Cloudio_Endpoint::getNode(string name)
{
    for(list<Cloudio_Node *>::iterator it = nodes.begin(); it!=nodes.end();it++){
        if((*it)->getName()==name){
            return (*it);
        }
    }
    Log::printD("Endpoint::getNode : Node not found");
    return nullptr;
}

string Cloudio_Endpoint::getUuid()
{
    return uuid;
}

void Cloudio_Endpoint::displayUuid()
{
    Log::printD(this->uuid);
}

Cloudio_Object *Cloudio_Endpoint::getObject(string topic)
{
    Cloudio_Object* retPtr = nullptr;
    Cloudio_Node* nodeTemp = nullptr;
    list<string> names = parseTopic(topic);
    list<string>::iterator it = names.begin();
    //iterator to go to last object
    list<string>::iterator itLast = names.end();
    //Control uuid
    if((*it)==this->uuid){
        //Go on the node name
        it++;
    }
    //UUID error, the control normally is useless since we are not subscribed to other topics on the server
    else {
        return nullptr;
    }
    //Get Node
    nodeTemp = getNode((*it));
    //Get first Object
    it++;
    retPtr=nodeTemp->getObject((*it));
    //parse tree of objects
    it++;
    for(;it!=itLast;it++){
        retPtr = retPtr->getObject((*it));
    }
    return retPtr;
}

Cloudio_Attribute *Cloudio_Endpoint::getAttribute(string topic)
{
    list<string> names = parseTopic(topic);
    //delete last element (the attribute)in the string but memorize his name
    int pos = topic.find_last_of('/');
    string temp = topic.substr(pos+1,topic.size()-1);
    topic = topic.substr(0,pos);
    //Get last object
    Cloudio_Object* ptrObject = getObject(topic);
    //Get Attribute
    Cloudio_Attribute* retVal = ptrObject->getAttribute(temp);
    return retVal;
}

Cloudio_Endpoint *Cloudio_Endpoint::getInstance()
{
    static Cloudio_Endpoint endpoint;
    return &endpoint;
}

json Cloudio_Endpoint::getJSON() const
{
    return j;
}

list<string> Cloudio_Endpoint::parseTopic(string topic)
{
    list<string> names;
    const string& delim="/";
    size_t prev = 0, pos = 0;
    do
    {
        pos = topic.find(delim, prev);
        if (pos == string::npos) pos = topic.length();
        string token = topic.substr(prev, pos-prev);
        if (!token.empty()) names.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < topic.length() && prev < topic.length());
    return names;
}

void Cloudio_Endpoint::makeJSON()
{
    j["endpointUuid"]= this->uuid;
    j["online"]=this->online;

    for(list<Cloudio_Node *>::iterator it = nodes.begin(); it!=nodes.end();it++){
        j["nodes"][(*it)->getName()]=nodeJSON(*it);
    }
    //Log::printD(j.dump(4));
}

json Cloudio_Endpoint::makeJSON_DataModel()
{
    json dataModel;
    dataModel["supportedFormats"]={"JSON"};
    dataModel["version"]="v0.2";
    for(list<Cloudio_Node *>::iterator it = nodes.begin(); it!=nodes.end();it++){
        dataModel["nodes"][(*it)->getName()]=nodeJSON(*it);
    }
    return dataModel;
}

json Cloudio_Endpoint::attributeJSON(Cloudio_Attribute *attribute)
{
    json retVal;
    retVal["constraint"]=attribute->constraintToString();
    retVal["type"]=attribute->type;
    retVal["timestamp"]=attribute->timestamp;
    if(attribute->type=="Number"){
        retVal["value"]=stof(attribute->getValue());
    }
    else if(attribute->type=="Integer"){
        retVal["value"]=stoi(attribute->getValue());
    }
    else{
        retVal["value"]=attribute->getValue();
    }
    return retVal;
}

json Cloudio_Endpoint::objectJSON(Cloudio_Object *object)
{
    json retVal;
    for(list<Cloudio_Attribute *>::iterator it = object->attributes.begin(); it!=object->attributes.end();it++){
        retVal["attributes"][(*it)->getName()] = attributeJSON(*it);
    }
    for(list<Cloudio_Object *>::iterator it = object->objects.begin(); it!=object->objects.end();it++){
        retVal["objects"][(*it)->getName()] = objectJSON(*it);
    }
    return retVal;
}

json Cloudio_Endpoint::nodeJSON(Cloudio_Node *node)
{
    json retVal;
    //No idea about what is implements, but the server need one object in the array, so....
    retVal["implements"] = {"None"};
    for(list<Cloudio_Object *>::iterator it = node->objects.begin(); it!=node->objects.end();it++){
        retVal["objects"][(*it)->getName()] = objectJSON(*it);
    }
    return retVal;
}
