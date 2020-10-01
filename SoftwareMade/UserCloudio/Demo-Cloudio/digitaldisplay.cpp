#include "digitaldisplay.h"

DigitalDisplay::DigitalDisplay()
{
    this->setFixedSize(QSize(400, 200));
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    this->move(10,700);
    this->setWindowTitle ( QString("Endpoint Information:") );

    this->setPoint.setText("Setpoint : no info");

    this->lblqt.setText("Endpoint on qt");

    this->lbltemp1qt.setText("Temperature bedroom : no info");
    this->lbltemp2qt.setText("Temperature kitchen : no info");

    QFont font = setPoint.font();
    font.setPointSize(14);
    font.setBold(true);
    setPoint.setFont(font);
    lblqt.setFont(font);
    lbltemp1qt.setFont(font);
    lbltemp2qt.setFont(font);
    onlineqt.setFont(font);
    /*
    this->lblnrf.setText("Endpoint on nrf");
    this->lbltemp1nrf.setText("Temperature bedroom : no info");
    this->lbltemp2nrf.setText("Temperature kitchen : no info");
    this->onlinenrf.setText("Offline");
    */
    this->onlineqt.setText("Offline");


    QVBoxLayout *myLayout=new QVBoxLayout(this);

    myLayout->addWidget(&setPoint);
    myLayout->addWidget(&lblqt);
    myLayout->addWidget(&lbltemp1qt);
    myLayout->addWidget(&lbltemp2qt);
    myLayout->addWidget(&onlineqt);
    //myLayout->addWidget(&lblnrf);
    //myLayout->addWidget(&lbltemp1nrf);
    //myLayout->addWidget(&lbltemp2nrf);
    //myLayout->addWidget(&onlinenrf);

    this->show();
}


void DigitalDisplay::setInfo(int owner, double temp1, double temp2, int online, int setPoint)
{
    this->setPoint.setText("SetPoint value : "+QString::number(setPoint)+"°");
    if(owner==0){
        this->lbltemp1qt.setText("Temperature bedroom : "+QString::number(temp1)+"°");
        this->lbltemp2qt.setText("Temperature kitchen : "+QString::number(temp2)+"°");
        if(online==0){
            this->onlineqt.setText("Offline");
        }
        else{
            this->onlineqt.setText("Online");
        }
    }
    else{
        /*
        this->lbltemp1nrf.setText("Temperature bedroom : "+QString::number(temp1)+"°");
        this->lbltemp2nrf.setText("Temperature kitchen : "+QString::number(temp2)+"°");
        if(online==1){
            this->onlineqt.setText("Offline");
        }
        else{
            this->onlineqt.setText("Online");
        }
        */
    }
}
