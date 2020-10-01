#include "node.h"

#include "endpoint.h"

Cloudio_Node::Cloudio_Node(string name)
{
    this->name=name;
    this->parent=nullptr;
}

Cloudio_Node::~Cloudio_Node()
{
    this->parent=nullptr;
    for(list<Cloudio_Object*>::iterator it=objects.begin() ; it!=objects.end();){
        delete *it;
        it=objects.erase(it);
    }
}

Cloudio_Object *Cloudio_Node::getObject(string name)
{
    for(list<Cloudio_Object*>::iterator it = objects.begin(); it!=objects.end();it++){
        if((*it)->getName()==name){
            return (*it);
        }
    }
    Log::printD("Endpoint::getNode : Node not found");
    return nullptr;
}

void Cloudio_Node::addObject(Cloudio_Object *object)
{
    if(this->parent==nullptr){
        Log::printD("Node::addObject : This node wasn't added to an Endpoint so Object insertion is denied.");
    }
    else{
        bool errorName=false;
        //Check if the name hasn't special character
        errorName = Topic::hasSpecialChar(object->getName());
        //Check if the name isn't already taken
        if(errorName==false){
            for(list<Cloudio_Object *>::iterator it = objects.begin(); it!=objects.end() && errorName==false;it++){
                if((*it)->name==object->name){
                    errorName=true;
                    Log::printD("Node::addObject : Name of Object already taken in this Object!");
                }
            }
        }
        else{
            Log::printD("Node::addObject : Name of Object possesses special character");
        }
        if(errorName==false){
            if(object->parentNode==nullptr && object->parentObject == nullptr){
                objects.push_front(object);
                object->setParent(this);
                object->topic=Topic::setTopic(object);
            }
            else {
                Log::printD("Node::addObject : Object was already added to an Object/Node!");
            }
        }
    }
}

void Cloudio_Node::removeObject(Cloudio_Object *object)
{
    bool foundName=false;
    for(list<Cloudio_Object *>::iterator it = objects.begin(); it!=objects.end() && foundName==false;it++){
        if((*it)->name==object->name){
            foundName=true;
            delete *it;
            objects.erase(it);
        }
    }
    if(foundName==true){
        I_Logger::getInstance()->logPrint("Node::removeObject : Object deleted");
    }
    else {
        I_Logger::getInstance()->logPrint("Node::removeObject : Object not found");
    }
}

Cloudio_Endpoint *Cloudio_Node::getParent()
{
    return this->parent;
}

string Cloudio_Node::getName()
{
    return this->name;
}

void Cloudio_Node::displayTopic()
{
    Log::printD(this->topic);
}

void Cloudio_Node::setParent(Cloudio_Endpoint * endpoint)
{
    this->parent=endpoint;
}

string Cloudio_Node::getTopic() const
{
    return topic;
}
