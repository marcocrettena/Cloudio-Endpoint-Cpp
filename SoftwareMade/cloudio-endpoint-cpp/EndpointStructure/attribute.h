#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <list>
#include <iostream>

#include "Interface/i_logger.h"

#include "Utility/topic.h"

using namespace std;

//TODO if I have time : Replace this useless hierarchy by a template class, harder but will prevent this horrible redondancy code

/**
 * @brief The Constraint enum
 * Enumeration that contain information about what is the attribute.
 * Broker's interaction with attribute can differ depends on the constraint the attribute has
 */
enum Constraint{
    Measure,
    Parameter,
    SetPoint,
    Status,
    StaticAttribute
};

class Cloudio_Object;
class EndpointController;

/**
 * @brief The Attribute class
 * The atomic object of our object : an attribute is the value which we want to know, for example a temperature.
 * This value can be of different type (string, double, integer or bool) and different constraint (for example
 * a setPoint or a measure, these two types must have different behavior)
 */
class Cloudio_Attribute
{
    friend Cloudio_Object;
    friend Cloudio_Endpoint;
    friend EndpointController;
    friend Topic;
protected:
    /**
     * @brief Attribute
     * Constructor
     * @param name
     * @param constraint
     */
    Cloudio_Attribute(string name,Constraint constraint);
    virtual ~Cloudio_Attribute();
protected:
    /**
     * @brief getParent
     * All Attributes should have an object who possess them, the object can be obtained
     * with this method
     * @return Object that contain the Attribute
     */
    Cloudio_Object* getParent();
    string getName();
    /**
     * @brief displayTopic
     * display the topic in the console
     */
    void displayTopic();
    string getTopic() const;
    virtual string getValue()=0;
    virtual void setValue(string value)=0;
    virtual void setValue(double value)=0;
    virtual void setValue(bool value)=0;
    virtual void setValue(int value)=0;

protected:
    /**
     * @brief checkConstraint
     * Method to check if the attribute's value can be modified, depend on the constraint the attribute has
     * @param sendError boolean to say if we should send the error message
     * @return true if the attribute's value can be modified, false otherwise
     */
    bool checkConstraint(bool sendError=true);
    void setParent(Cloudio_Object * object);
    /**
     * @brief constraintToString
     * @return string representing the constraint that the attribute has
     */
    string constraintToString();
    /**
     * @brief setTimestamps
     * Modify the timestamps value when the value of the attribute is modified
     */
    void setTimestamps();
protected:
    string name;                ///Name of the Attribute
    string type;                ///Type of the Attribute's value
    Constraint constraint;      ///Constraint of the Attribute
    Cloudio_Object* parent;     ///Object that possess this attribute
    long long timestamp;        ///Timestamps of the attribute
    string topic;                ///Topic of the Attribute
};

class AttributeString : public Cloudio_Attribute{
    friend EndpointController;
public:
    AttributeString(string name, Constraint constraint, string value);
    AttributeString(string name, Constraint constraint, string value,void (*callback)(string));

    string getValue();
private:
    string value;
    void (*callback)(string);               ///Callback function, will be called when the value changes from the server


    // Just to make this class not abstracted
protected:
    void setValue(string value);
    void changeValue(string value);
    void setValue(double value);
    void setValue(bool value);
    void setValue(int value);
};

class AttributeDouble : public Cloudio_Attribute{
    friend EndpointController;
public:
    AttributeDouble(string name, Constraint constraint, double value);
    AttributeDouble(string name, Constraint constraint, double value,void (*callback)(double));

    string getValue();
private:
    double value;
    void (*callback)(double);                ///Callback function, will be called when the value changes from the server


    // Just to make this class not abstracted
protected:
    void changeValue(double value);
    void setValue(double value);
    void setValue(string value);
    void setValue(bool value);
    void setValue(int value);
};

class AttributeInt : public Cloudio_Attribute{
    friend EndpointController;
public:
    AttributeInt(string name, Constraint constraint, int value);
    AttributeInt(string name, Constraint constraint, int value,void (*callback)(int));

    string getValue();
private:
    int value;
    void (*callback)(int);                  ///Callback function, will be called when the value changes from the server


    // Just to make this class not abstracted
protected:
    void setValue(int value);
    void changeValue(int value);
    void setValue(double value);
    void setValue(bool value);
    void setValue(string value);
};

class AttributeBool : public Cloudio_Attribute{
    friend EndpointController;
public:
    AttributeBool(string name, Constraint constraint, bool value);
    AttributeBool(string name, Constraint constraint, bool value,void (*callback)(bool));

    string getValue();
private:
    bool value;
    void (*callback)(bool);                 ///Callback function, will be called when the value changes from the server


    // Just to make this class not abstracted
protected:
    void setValue(bool value);
    void changeValue(bool value);
    void setValue(double value);
    void setValue(string value);
    void setValue(int value);
};
#endif // ATTRIBUTE_H
