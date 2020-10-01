#ifndef CAPTORPOLL_H
#define CAPTORPOLL_H
#include <QTimer>
#include "EndpointStructure/attribute.h"
#include "cstdlib"

class CaptorPoll : public QObject
{
    Q_OBJECT
public:
    CaptorPoll(AttributeDouble* attrKitchen, AttributeDouble* attrBedroom);
private:
    QTimer* timer;
    int setPointTemp;
    AttributeDouble* attrKitchen;
    AttributeDouble* attrBedroom;
public:
    int getSetPointTemp() const;
    void setSetPointTemp(int value);
    void pollCaptor(AttributeDouble* attr);
};

#endif // CAPTORPOLL_H
