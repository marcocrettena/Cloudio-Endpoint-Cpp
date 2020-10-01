#include <QPalette>
#include "controlpanel.h"

ControlPanel::ControlPanel()
{
    start=new QPushButton("Begin");
    stop=new QPushButton("Stop");
    sendRequest=new QPushButton("Request");
    lblValue=new QLabel();
    value = new QLineEdit();

    start->setFixedSize(80,80);
    stop->setFixedSize(80,80);
    sendRequest->setFixedSize(80,80);

    QPalette pal1 = start->palette();
    pal1.setColor(QPalette::Button, QColor(Qt::green));
    start->setAutoFillBackground(true);
    start->setFlat(true);
    start->setPalette(pal1);
    start->update();

    QPalette pal2 = stop->palette();
    pal2.setColor(QPalette::Button, QColor(Qt::red));
    stop->setAutoFillBackground(true);
    stop->setFlat(true);
    stop->setPalette(pal2);
    stop->update();

    QPalette pal3 = sendRequest->palette();
    pal3.setColor(QPalette::Button, QColor(Qt::yellow));
    sendRequest->setAutoFillBackground(true);
    sendRequest->setFlat(true);
    sendRequest->setPalette(pal3);
    sendRequest->update();

    lblValue->setText("Value SetPoint:");
    value->setText("");


    QHBoxLayout *layout=new QHBoxLayout;
    layout->addWidget(start);
    layout->addWidget(stop);
    layout->addWidget(sendRequest);
    layout->addWidget(lblValue);
    layout->addWidget(value);
    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);

    this->setFixedSize(QSize(400, 100));
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    this->move(10,550);
    this->setWindowTitle ( QString("Control Panel") );
    this->show();
}

ControlPanel::~ControlPanel()
{

}

QPushButton * ControlPanel::getPbStart()
{
    return start;
}

QPushButton * ControlPanel::getPbStop()
{
    return stop;
}

QPushButton *ControlPanel::getPbRequest()
{
    return sendRequest;
}

int ControlPanel::getValue()
{
    QString s = this->value->text();
    int value = s.toInt();
    return value;
}
