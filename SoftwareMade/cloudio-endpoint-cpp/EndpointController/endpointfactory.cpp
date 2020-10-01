#include "endpointfactory.h"
#include "EndpointStructure/endpoint.h"
#include "EndpointStructure/node.h"
#include "EndpointStructure/object.h"

EndpointFactory::EndpointFactory()
{
    this->endpoint=Cloudio_Endpoint::getInstance();
}

EndpointFactory *EndpointFactory::getInstance()
{
    static EndpointFactory ef;
    return &ef;
}

Cloudio_Node *EndpointFactory::addNode(string name)
{
    Cloudio_Node* node =new Cloudio_Node(name);
    endpoint->addNode(node);
    return node;
}

void EndpointFactory::removeNode(string name)
{
    removeNode(endpoint->getNode(name));
}

void EndpointFactory::removeNode(Cloudio_Node *node)
{
    endpoint->removeNode(node);
}

Cloudio_Object *EndpointFactory::addObject(Cloudio_Node *parent, string name)
{
    Cloudio_Object* object = new Cloudio_Object(name);
    parent->addObject(object);
    return object;
}

Cloudio_Object *EndpointFactory::addObject(Cloudio_Object *parent, string name)
{
    Cloudio_Object* object = new Cloudio_Object(name);
    parent->addObject(object);
    return object;
}

AttributeInt *EndpointFactory::addAttribute(Cloudio_Object *parent, string name, Constraint constraint, int initValue, void (*callback)(int))
{
    AttributeInt* attribute = new AttributeInt(name,constraint,initValue,callback);
    parent->addAttribute(attribute);
    return attribute;
}

AttributeString *EndpointFactory::addAttribute(Cloudio_Object *parent, string name, Constraint constraint, string initValue, void (*callback)(string))
{
    AttributeString* attribute = new AttributeString(name,constraint,initValue,callback);
    parent->addAttribute(attribute);
    return attribute;
}

AttributeDouble *EndpointFactory::addAttribute(Cloudio_Object *parent, string name, Constraint constraint, double initValue, void (*callback)(double))
{
    AttributeDouble* attribute = new AttributeDouble(name,constraint,initValue,callback);
    parent->addAttribute(attribute);
    return attribute;
}

AttributeBool *EndpointFactory::addAttribute(Cloudio_Object *parent, string name, Constraint constraint, bool initValue, void (*callback)(bool))
{
    AttributeBool* attribute = new AttributeBool(name,constraint,initValue,callback);
    parent->addAttribute(attribute);
    return attribute;
}

AttributeInt *EndpointFactory::addAttribute(Cloudio_Object *parent, string name, Constraint constraint, int initValue)
{
    AttributeInt* attribute = new AttributeInt(name,constraint,initValue);
    parent->addAttribute(attribute);
    return attribute;
}

AttributeString *EndpointFactory::addAttribute(Cloudio_Object *parent, string name, Constraint constraint, string initValue)
{
    AttributeString* attribute = new AttributeString(name,constraint,initValue);
    parent->addAttribute(attribute);
    return attribute;
}

AttributeDouble *EndpointFactory::addAttribute(Cloudio_Object *parent, string name, Constraint constraint, double initValue)
{
    AttributeDouble* attribute = new AttributeDouble(name,constraint,initValue);
    parent->addAttribute(attribute);
    return attribute;
}

AttributeBool *EndpointFactory::addAttribute(Cloudio_Object *parent, string name, Constraint constraint, bool initValue)
{
    AttributeBool* attribute = new AttributeBool(name,constraint,initValue);
    parent->addAttribute(attribute);
    return attribute;
}
