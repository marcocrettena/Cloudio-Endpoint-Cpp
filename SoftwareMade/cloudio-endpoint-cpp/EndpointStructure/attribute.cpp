#include "attribute.h"
#include "Interface/resourcefactory.h"
#include "object.h"


Cloudio_Attribute::Cloudio_Attribute(string name, Constraint constraint)
{
    this->constraint=constraint;
    this->name=name;
    this->type="";
    this->parent=nullptr;
}

Cloudio_Attribute::~Cloudio_Attribute()
{
    this->parent=nullptr;
}

Cloudio_Object *Cloudio_Attribute::getParent()
{
    return this->parent;
}

string Cloudio_Attribute::getName()
{
    return this->name;
}

void Cloudio_Attribute::displayTopic()
{
    Log::printD(this->topic);
}

void Cloudio_Attribute::setParent(Cloudio_Object * object)
{
    this->parent=object;
}

string Cloudio_Attribute::constraintToString()
{
    switch(this->constraint){
        case Constraint::Status :
            return "Status";
        case Constraint::Measure :
            return "Measure";
        case Constraint::SetPoint :
            return "SetPoint";
        case Constraint::Parameter :
            return "Parameter";
        case Constraint::StaticAttribute :
            return "StaticAttribute";
    }
    return "";
}

void Cloudio_Attribute::setTimestamps()
{
    this->timestamp = ResourceFactory::getInstance()->getTimestamp();
}

string Cloudio_Attribute::getTopic() const
{
    return topic;
}

bool Cloudio_Attribute::checkConstraint(bool sendError)
{
    if(this->constraint==Constraint::Parameter || this->constraint==Constraint::SetPoint){
        return true;
    }
    else {
        if(sendError){
            Log::printD("Attribute::checkConstraint : Can not change an attribute with constraint");

            switch (this->constraint) {
                case Constraint::Measure:
                    Log::printD("Measure");
                    break;
                case Constraint::Status:
                    Log::printD("Status");
                    break;
                case Constraint::StaticAttribute:
                    Log::printD("Static attribute");
                    break;
                default:
                    break;
            }
            return false;
        }
    }
}

AttributeString::AttributeString(string name, Constraint constraint, string value) : Cloudio_Attribute(name, constraint)
{
    this->value=value;
    setTimestamps();
    this->type="String";
    if(!checkConstraint(false)){
        callback=nullptr;
    }
    else {
        Log::printD("Attribute Constructor: couldn't be used efficiently, no callback function with this constraint makes this attribute useless");
        callback=nullptr;
    }
}

AttributeString::AttributeString(string name, Constraint constraint, string value, void (*callback)(string)): Cloudio_Attribute(name, constraint)
{
    this->value=value;
    setTimestamps();
    this->type="String";
    this->callback=callback;
    if(!checkConstraint(false) && callback != nullptr){
        Log::printD("Attribute Constructor: callback useless with this constraint");
    }
}

void AttributeString::setValue(string value)
{
    bool canBeSet;
    canBeSet = this->checkConstraint();
    if(canBeSet==true){
        this->value=value;
        setTimestamps();
        if(this->callback!=nullptr){
            callback(value);
        }
        else {
            Log::printD("Attribute::setValue : no callback function for this value");
        }
    }
}

void AttributeString::changeValue(string value)
{
    this->value=value;
    setTimestamps();
}

string AttributeString::getValue()
{
    return this->value;
}

void AttributeString::setValue(double value)
{
    Log::printD("Wrong type to set value of this attribute");
}

void AttributeString::setValue(bool value)
{
    Log::printD("Wrong type to set value of this attribute");
}

void AttributeString::setValue(int value)
{
    Log::printD("Wrong type to set value of this attribute");
}

AttributeDouble::AttributeDouble(string name, Constraint constraint, double value) : Cloudio_Attribute(name, constraint)
{
    this->value=value;
    setTimestamps();
    this->type="Number";
    if(!checkConstraint(false)){
        callback=nullptr;
    }
    else {
        Log::printD("Attribute Constructor: couldn't be used efficiently, no callback function with this constraint makes this attribute useless");
        callback=nullptr;
    }
}

AttributeDouble::AttributeDouble(string name, Constraint constraint, double value, void (*callback)(double)): Cloudio_Attribute(name, constraint)
{
    this->value=value;
    setTimestamps();
    this->type="Number";
    this->callback=callback;
    if(!checkConstraint(false) && callback != nullptr){
        Log::printD("Attribute Constructor: callback useless with this constraint");
    }

}

void AttributeDouble::setValue(double value)
{
    bool canBeSet;
    canBeSet = this->checkConstraint();
    if(canBeSet==true){
        this->value=value;
        setTimestamps();
        if(this->callback!=nullptr){
            callback(value);
        }
        else {
            Log::printD("Attribute::setValue : no callback function for this value");
        }
    }
}

string AttributeDouble::getValue()
{
    return to_string(this->value);
}

void AttributeDouble::changeValue(double value)
{
    this->value=value;
    setTimestamps();
}

void AttributeDouble::setValue(string value)
{
    Log::printD("Wrong type to set value of this attribute");
}

void AttributeDouble::setValue(bool value)
{
    Log::printD("Wrong type to set value of this attribute");
}

void AttributeDouble::setValue(int value)
{
    Log::printD("Wrong type to set value of this attribute");
}

AttributeBool::AttributeBool(string name, Constraint constraint, bool value) : Cloudio_Attribute(name, constraint)
{
    this->value=value;
    setTimestamps();
    this->type="Boolean";
    if(!checkConstraint(false)){
        callback=nullptr;
    }
    else {
        Log::printD("Attribute Constructor: couldn't be used efficiently, no callback function with this constraint makes this attribute useless");
        callback=nullptr;
    }
}

AttributeBool::AttributeBool(string name, Constraint constraint, bool value, void (*callback)(bool)) : Cloudio_Attribute(name, constraint)
{
    this->value=value;
    setTimestamps();
    this->type="Boolean";
    this->callback=callback;
    if(!checkConstraint(false) && callback != nullptr){
        Log::printD("Attribute Constructor: callback useless with this constraint");
    }
}

void AttributeBool::setValue(bool value)
{
    bool canBeSet;
    canBeSet = this->checkConstraint();
    if(canBeSet==true){
        this->value=value;
        setTimestamps();
        if(this->callback!=nullptr){
            callback(value);
        }
        else {
            Log::printD("Attribute::setValue : no callback function for this value");
        }
    }
}

void AttributeBool::changeValue(bool value)
{
    this->value=value;
    setTimestamps();
}

string AttributeBool::getValue()
{
    return to_string(this->value);
}

void AttributeBool::setValue(double value)
{
    Log::printD("Wrong type to set value of this attribute");
}

void AttributeBool::setValue(string value)
{
    Log::printD("Wrong type to set value of this attribute");
}

void AttributeBool::setValue(int value)
{
    Log::printD("Wrong type to set value of this attribute");
}

AttributeInt::AttributeInt(string name, Constraint constraint, int value) : Cloudio_Attribute(name, constraint)
{
    this->value=value;
    setTimestamps();
    this->type="Integer";
    if(!checkConstraint(false)){
        callback=nullptr;
    }
    else {
        Log::printD("Attribute Constructor: couldn't be used efficiently, no callback function with this constraint makes this attribute useless");
        callback=nullptr;
    }
}

AttributeInt::AttributeInt(string name, Constraint constraint, int value, void (*callback)(int)) : Cloudio_Attribute(name, constraint)
{
    this->value=value;
    this->type="Integer";
    setTimestamps();
    this->callback=callback;
    if(!checkConstraint(false) && callback != nullptr){
        Log::printD("Attribute Constructor: callback useless with this constraint");
    }
}

void AttributeInt::setValue(int value)
{
    bool canBeSet;
    canBeSet = this->checkConstraint();
    if(canBeSet==true){
        this->value=value;
        setTimestamps();
        if(this->callback!=nullptr){
            callback(value);
        }
        else {
            Log::printD("Attribute::setValue : no callback function for this value");
        }
    }
}

void AttributeInt::changeValue(int value)
{
    this->value=value;
    setTimestamps();
}

string AttributeInt::getValue()
{
    return to_string(this->value);
}

void AttributeInt::setValue(double value)
{
    Log::printD("Wrong type to set value of this attribute");
}

void AttributeInt::setValue(bool value)
{
    Log::printD("Wrong type to set value of this attribute");
}

void AttributeInt::setValue(string value)
{
    Log::printD("Wrong type to set value of this attribute");
}


