#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    ControlPanel();
    ~ControlPanel();
    QPushButton * getPbStart();
    QPushButton * getPbStop();
    QPushButton * getPbRequest();
    int getValue();
private:
    QPushButton * start;
    QPushButton * stop;
    QPushButton * sendRequest;
    QLabel * lblValue;
    QLineEdit * value;
};

#endif // CONTROLPANEL_H
