#include "object.h"
#include "node.h"

Cloudio_Object::Cloudio_Object(string name)
{
    this->name=name;
    this->parentNode=nullptr;
    this->parentObject=nullptr;
}

Cloudio_Object::~Cloudio_Object()
{
    this->parentNode=nullptr;
    this->parentObject=nullptr;
    //Delete all objects from list
    for(list<Cloudio_Object*>::iterator it=objects.begin() ; it!=objects.end();){
        delete *it;
        it=objects.erase(it);
    }
    //Delete all attributes from list
    for(list<Cloudio_Attribute*>::iterator it=attributes.begin() ; it!=attributes.end();){
        delete *it;
        it=attributes.erase(it);
    }
}

Cloudio_Object *Cloudio_Object::getObject(string name)
{
    for(list<Cloudio_Object*>::iterator it = objects.begin(); it!=objects.end();it++){
        if((*it)->getName()==name){
            return (*it);
        }
    }
    Log::printD("Cloudio_Object::getObject : Object not found");
    return nullptr;
}

Cloudio_Attribute *Cloudio_Object::getAttribute(string name)
{
    for(list<Cloudio_Attribute*>::iterator it = attributes.begin(); it!=attributes.end();it++){
        if((*it)->getName()==name){
            return (*it);
        }
    }
    Log::printD("Cloudio_Object::getObject : Attribute not found");
    return nullptr;
}

void Cloudio_Object::addObject(Cloudio_Object *object)
{
    //An Object can possess an Object if he is already set in the "tree"
    if(this->parentNode==nullptr && this->parentObject==nullptr){
        Log::printD("Cloudio_Object::addObject : this object wasn't added to a Node so object insertion is denied.");
    }
    else {
        bool errorName=false;
        //Check if the name hasn't special character
        errorName = Topic::hasSpecialChar(object->getName());
        //Check if the name isn't already taken
        if(errorName==false){
            for(list<Cloudio_Object *>::iterator it = objects.begin(); it!=objects.end() && errorName==false;it++){
                if((*it)->name==object->name){
                    errorName=true;
                    Log::printD("Cloudio_Object::addObject : Name of Ojbect already taken in this Object!");
                }
            }
            /* Shouldn't be a problem to let an object and an attribute to have the same name
            for(list<Cloudio_Attribute *>::iterator it = attributes.begin(); it!=attributes.end() && errorName==false;it++){
                if((*it)->name==object->name){
                    errorName=true;
                    Log::printD("Cloudio_Object::addAttribute : Name of Attribute already taken in this Object!");
                }
            }
            */
        }
        else{
            Log::printD("Cloudio_Object::addObject : Name of Object possesses special character");
        }
        if(errorName==false){
            if(object->parentNode==nullptr && object->parentObject == nullptr){
                objects.push_front(object);
                object->setParent(this);
                object->topic=Topic::setTopic(object);
            }
            else {
                Log::printD("Cloudio_Object::addObject : Object was already added to an Object/Node!");
            }
        }
    }
}

void Cloudio_Object::addAttribute(Cloudio_Attribute* attribute)
{
    //An Object can possess an Attribute if he is already set in the "tree"
    if(this->parentNode==nullptr && this->parentObject==nullptr){
        Log::printD("Cloudio_Object::addAttribute : this object wasn't added to a Node so attribute insertion is denied.");
    }
    else {
        bool errorName=false;
        //Check if the name hasn't special character
        errorName = Topic::hasSpecialChar(attribute->getName());
        //Check if the name isn't already taken
        if(errorName==false){
            /* Shouldn't be a problem to let an object and an attribute to have the same name
            for(list<Cloudio_Object *>::iterator it = objects.begin(); it!=objects.end() && foundName==false;it++){
                if((*it)->name==attribute->name){
                    foundName=true;
                    Log::printD("Cloudio_Object::addObject : Name of Object already taken in this Object!");
                }
            }
            */
            for(list<Cloudio_Attribute *>::iterator it = attributes.begin(); it!=attributes.end() && errorName==false;it++){
                if((*it)->name==attribute->name){
                    errorName=true;
                    Log::printD("Cloudio_Object::addAttribute : Name of Attribute already taken in this Object!");
                }
            }
        }
        else{
            Log::printD("Cloudio_Object::addAttribute : Name of Attribute possesses special character");
        }
        if(errorName==false){
            if(attribute->parent==nullptr){
                attributes.push_front(attribute);
                attribute->setParent(this);
                attribute->topic=Topic::setTopic(attribute);
            }
            else {
                Log::printD("Cloudio_Object::addAttribute : Attribute was already added to an Object!");
            }
        }
    }
}

void Cloudio_Object::removeObject(Cloudio_Object *object)
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
        I_Logger::getInstance()->logPrint("Cloudio_Object::removeObject : Object deleted");
    }
    else {
        I_Logger::getInstance()->logPrint("Cloudio_Object::removeObject : Object not found");
    }
}

void Cloudio_Object::removeAttribute(Cloudio_Attribute *attribute)
{
    bool foundName=false;
    for(list<Cloudio_Attribute *>::iterator it = attributes.begin(); it!=attributes.end() && foundName==false;it++){
        if((*it)->name==attribute->name){
            foundName=true;
            delete *it;
            attributes.erase(it);
        }
    }
    if(foundName==true){
        I_Logger::getInstance()->logPrint("Cloudio_Object::removeAttribute : Attribute deleted");
    }
    else {
        I_Logger::getInstance()->logPrint("Cloudio_Object::removeAttribute : Attribute not found");
    }
}

Cloudio_Object *Cloudio_Object::getParentObject()
{
    return this->parentObject;
}

Cloudio_Node *Cloudio_Object::getParentNode()
{
    return this->parentNode;
}

string Cloudio_Object::getName()
{
    return this->name;
}

void Cloudio_Object::displayTopic()
{
    Log::printD(this->topic);
}

void Cloudio_Object::setParent(Cloudio_Object *object)
{
    if(this->parentNode==nullptr && this->parentObject==nullptr){
        this->parentObject=object;
    }
    else {
        Log::printD("Cloudio_object : this object has already a parent");
    }
}

void Cloudio_Object::setParent(Cloudio_Node *node)
{
    if(this->parentNode==nullptr && this->parentObject==nullptr){
        this->parentNode=node;
    }
    else {
        Log::printD("Cloudio_object : this object has already a parent");
    }

}

string Cloudio_Object::getTopic() const
{
    return topic;
}
