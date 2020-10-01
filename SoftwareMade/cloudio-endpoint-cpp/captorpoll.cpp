#include "captorpoll.h"
#include "EndpointController/endpointcontroller.h"

CaptorPoll::CaptorPoll(AttributeDouble* attrKitchen, AttributeDouble* attrBedroom)
{
    this->attrBedroom = attrBedroom;
    this->attrKitchen = attrKitchen;
    setPointTemp=20;
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout,[this](){
            pollCaptor(this->attrBedroom);
            pollCaptor(this->attrKitchen);
    });
    timer->start(2000);
}

int CaptorPoll::getSetPointTemp() const
{
    return setPointTemp;
}

void CaptorPoll::setSetPointTemp(int value)
{
    setPointTemp = value;
}

void CaptorPoll::pollCaptor(AttributeDouble *attr)
{
    double newValue;
    double attrValue = stod(attr->getValue());
    //Random value
    double changes = ((double)(rand() % 50))/50.0f;
    if(attrValue<setPointTemp){
        newValue = attrValue+changes;
    }
    else{
        newValue = attrValue-changes;
    }
    // Function to modify the value of an attribute
    EndpointController::getInstance()->setAttributeValue(attr,newValue);
}
