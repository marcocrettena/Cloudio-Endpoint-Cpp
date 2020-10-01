#ifndef DIGITALDISPLAY_H
#define DIGITALDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <displaybase.h>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFont>

class DigitalDisplay : public DisplayBase
{
    Q_OBJECT
public:
    DigitalDisplay();
private:
    QLabel lblnrf;
    QLabel lblqt;
    QLabel lbltemp1nrf;
    QLabel lbltemp2nrf;
    QLabel lbltemp1qt;
    QLabel lbltemp2qt;
    QLabel onlinenrf;
    QLabel onlineqt;
    QLabel setPoint;

public slots:
    void setInfo(int owner, double temp1, double temp2, int online, int setPoint);

};

#endif // DIGITALDISPLAY_H
