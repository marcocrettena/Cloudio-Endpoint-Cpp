#include "topic.h"

#include "EndpointStructure/attribute.h"
#include "EndpointStructure/object.h"
#include "EndpointStructure/node.h"
#include "EndpointStructure/endpoint.h"

Topic::Topic()
{
}

string Topic::setTopic(Cloudio_Attribute* attribute)
{
    if(attribute->getParent()!=nullptr){
        string temp;
        string topic=string(attribute->getName());
        topic="/"+topic;

        Cloudio_Object* object=attribute->getParent();
        temp=string(object->getName());
        topic="/"+temp+topic;

        Cloudio_Object* pParent = object->getParentObject();
        while(pParent!=nullptr){
            temp=string(pParent->getName());
            topic="/"+temp+topic;
            object = object->getParentObject();
            pParent = object->getParentObject();
        }
        if(object->getParentNode()==nullptr){
            Log::printD("setTopicUuid Attribute : An error occurs in the tree (Object no Node parent): How did you make that?");
            return "";
        }
        else {
            temp=string(object->getParentNode()->getName());
            topic="/"+temp+topic;
            if(object->getParentNode()->getParent()==nullptr){
                Log::printD("setTopicUuid Attribute : An error occurs in the tree (Node no Endpoint parent): How did you make that?");
                return "";
            }
            else {
                temp=string(object->getParentNode()->getParent()->getUuid());
                topic="/"+temp+topic;
                return topic;
            }
        }
    }
    else {
        Log::printD("setTopicUuid Attribute : An error occurs in the tree: Attribute wasn't added to an Object.");
        return "";
    }
}

string Topic::setTopic(Cloudio_Object* object)
{
    if(object->getParentObject()!=nullptr || object->getParentNode()!=nullptr){
        string temp;
        string topic=string(object->getName());
        topic="/"+topic;
        Cloudio_Node* pNodeParent = object->getParentNode();

        if(pNodeParent==nullptr){
            Cloudio_Object* objectTemp=object->getParentObject();
            temp=string(objectTemp->getName());
            topic="/"+temp+topic;

            Cloudio_Object* pParent = objectTemp->getParentObject();
            while(pParent!=nullptr){
                temp=string(pParent->getName());
                topic="/"+temp+topic;
                objectTemp = objectTemp->getParentObject();
                pParent = objectTemp->getParentObject();
            }
            pNodeParent=objectTemp->getParentNode();
        }
        if(pNodeParent->getParent()==nullptr){
            Log::printD("setTopicUuid Object : An error occurs in the tree (Node no Endpoint parent): How did you make that?");
            return "";
        }
        else {
            temp=string(pNodeParent->getName());
            topic="/"+temp+topic;
            temp=string(pNodeParent->getParent()->getUuid());
            topic="/"+temp+topic;
            return topic;
        }
    }
    else {
        Log::printD("setTopicUuid Object : An error occurs in the tree: Object wasn't added to an Object/Node");
        return "";
    }
}

string Topic::setTopic(Cloudio_Node* node)
{
    if(node->getParent()!=nullptr){
        string temp;
        string topic=string(node->getName());
        topic="/"+topic;
        temp=string(node->getParent()->getUuid());
        topic="/"+temp+topic;
        return topic;
    }
    else {
        Log::printD("setTopicUuid Node : An error occurs in the tree: Node wasn't added to an Endpoint.");
        return "";
    }
}

bool Topic::hasSpecialChar(string name)
{
    bool retVal=false;
    for(int i=0; i<name.length(); i++){
        if(name[i]<'0' && name[i]!='-'){
            retVal=true;
        }
        if(name[i]>'9' && name[i]<'A'){
            retVal=true;
        }
        if(name[i]>'Z' && name[i]<'a' && name[i]!='_'){
            retVal=true;
        }
        if(name[i]>'z'){
            retVal=true;
        }
    }
    return retVal;
}


