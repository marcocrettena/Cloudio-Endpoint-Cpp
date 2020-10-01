#ifndef CONTROLLERWINDOW_H
#define CONTROLLERWINDOW_H

#include <QMainWindow>
#include <controlpanel.h>
#include <digitaldisplay.h>
#include <graficdisplay.h>
#include <QList>

#include <QTimer>

#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFont>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QAuthenticator>

#include "json.hpp"

using json = nlohmann::json;

#include <iostream>

using namespace std;

#define HOSTNAME "10.93.9.213"
#define CLIENTNAME "admin"
#define PASSWORD "hLwdw32Db6Jl5SKd"
#define UUIDQT "89cb0dec-0178-428a-9327-93f1313c3982"


//Since QWidget inherits from QObject, ControllerWindow will inherits of QObject so can use signal/slot
class ControllerWindow : public QWidget
{
    //NEVER FORGET Q_OBJECT MACRO
    Q_OBJECT

public:
    ControllerWindow(QWidget *parent = 0);
    ~ControllerWindow();
private:
    //Useless attribute
    QTimer timer;

    //pointers to other window of the application
    ControlPanel * cp;
    DigitalDisplay * dd;
    GraphicDisplay *ad;
    QList<QWidget *> myList;

    //Server
    QString url_str;
    QNetworkAccessManager* manager;
    QNetworkRequest requestInfo;
    QNetworkRequest requestSetpoint;
    //Info of endpoint
    float temp1;
    float temp2;
    int online;
    //UUID of endpoint
    QString uuidNrf;
    QString uuidQT;

    QLabel * myLabel;
    QString s;
    bool isStop;
    QPushButton * clear;
    QTextEdit * text;

    // slots: special function that can be called by some emitted signals
public slots:
    //for the button
    void begin();
    void stop();
    void printStatus();
    void printTick();
    //print signal
    void sendRequest();
    void clearCache();
    void modifyRequest();

    void onAuthentificationRequestSlot(QNetworkReply* reply,QAuthenticator* authenticator);
    //Signal attached to slots of the horloges display, emitted when a second passed
signals:
    void sendStatus(int, double, double, int, int);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // CONTROLLERWINDOW_H
