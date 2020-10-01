#include "controllerwindow.h"

ControllerWindow::ControllerWindow(QWidget *parent) : QWidget(parent)
{
    s="";
    temp1=0;
    temp2=0;
    online=0;
    isStop=false;

    //windows manager
    this->setFixedSize(QSize(400, 500));
    this->move(10,10);
    this->setWindowTitle ( QString("Controller Window") );

    cp=new ControlPanel();
    dd=new DigitalDisplay();
    ad=new GraphicDisplay();

    myList.append(cp);
    myList.append(dd);
    myList.append(ad);

    QPushButton * start=cp->getPbStart();
    QPushButton * stop=cp->getPbStop();
    QPushButton * sendRequest=cp->getPbRequest();

    //label/Layout of main Window

    //textEdit to show the sigTicks and Status
    text = new QTextEdit(this);
    text->autoFillBackground();
    text->setReadOnly(true);
    text->setAlignment(Qt::AlignTop);
    text->setFontPointSize(8);

    //title of main window
    QLabel * title=new QLabel(this);
    QFont f( "Arial", 14, QFont::Bold);
    title->setFont(f);
    title->clear();
    title->setText("Control Output");
    title->update();

    //PB of main window
    clear=new QPushButton("Clear Control Input");
    QPalette pal1 = clear->palette();
    pal1.setColor(QPalette::Button, QColor(0,204,204));
    clear->setAutoFillBackground(true);
    clear->setFlat(true);
    clear->setPalette(pal1);
    clear->update();

    //Layout for title, text and PB
    QVBoxLayout *myLayout=new QVBoxLayout(this);
    myLayout->addWidget(title,10,Qt::AlignTop);
    myLayout->addWidget(text,100,0);//if alignement == 0, takes all the space
    myLayout->addWidget(clear,20,Qt::AlignBottom);



    //signal & slots

    connect(start,SIGNAL(clicked()),this,SLOT(begin()));
    connect(stop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(sendRequest, SIGNAL(clicked()),this,SLOT(modifyRequest()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(sendRequest()));
    connect(this,SIGNAL(sendStatus(int, double, double, int, int)),ad,SLOT(setInfo(int, double, double, int, int)));
    connect(this,SIGNAL(sendStatus(int, double, double, int, int)),dd,SLOT(setInfo(int, double, double, int, int)));
    connect(&timer,SIGNAL(timeout()),this,SLOT(printTick()));
    connect(start,SIGNAL(clicked()),this,SLOT(printStatus()));
    connect(stop,SIGNAL(clicked()),this,SLOT(printStatus()));
    connect(clear,SIGNAL(clicked()),this,SLOT(clearCache()));

    manager = new QNetworkAccessManager();
    connect(manager,&QNetworkAccessManager::finished,this,[=](QNetworkReply *reply){
       if(reply->error()){
           s.append(reply->errorString()); //<< reply->errorString();
           text->setText(s);
           return;
       }
       QString answer = reply->readAll();
       string s = answer.toStdString();
       json j = json::parse(s);
       if(j.contains("endpoint")){
           double temp1 = j["endpoint"]["nodes"]["Bedroom"]["objects"]["TempController"]["objects"]["TempMeasurement"]["attributes"]["BedroomTemp"]["value"];
           double temp2 = j["endpoint"]["nodes"]["Kitchen"]["objects"]["TempMeasurement"]["attributes"]["KitchenTemp"]["value"];
           int setPoint = j["endpoint"]["nodes"]["Bedroom"]["objects"]["TempController"]["attributes"]["SetTemp"]["value"];
           int isOnline=0;
           if(j["online"]){
               isOnline=1;
           }
           int owner=1;
           //QT
           if(j["endpointUuid"]=="89cb0dec-0178-428a-9327-93f1313c3982"){
               owner=0;
           }
           //nRF
           emit sendStatus(owner,temp1,temp2,isOnline,setPoint);
       }
       else{
           qDebug() <<answer;
       }
    });
    connect(manager,SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),this,SLOT(onAuthentificationRequestSlot(QNetworkReply*,QAuthenticator*)));
}

ControllerWindow::~ControllerWindow()
{


}

void ControllerWindow::begin()
{
    if(!timer.isActive()){
        timer.start(3000);
    }
}

void ControllerWindow::stop()
{

    if(timer.isActive()){
        timer.stop();
    }
}

void ControllerWindow::printStatus()
{
    if(timer.isActive())
    {
        s.append(QString("\nStatus: START"));
        isStop=false;
    }
    else{
        if(isStop){
            s.clear();
            s.append(QString("\nStatus: RESTART"));
        }
        else{
            s.append(QString("\nStatus: STOP"));
            isStop=true;
        }
    }
    text->setText(s);
}

void ControllerWindow::printTick()
{
    s.append(QString("\nsigRequest-->"));
    text->setText(s);
}

void ControllerWindow::sendRequest()
{
    requestInfo.setUrl(QUrl("http://"+QString(HOSTNAME)+"/api/v1/endpoints/89cb0dec-0178-428a-9327-93f1313c3982"));
    manager->get(requestInfo);
    /*
    request.setUrl(QUrl("http://153.109.15.40/api/v1/endpoints/5d0f6457-8ab4-4ee2-9363-438f2de5b278"));
    manager->get(request);
    */
}

void ControllerWindow::clearCache()
{
    s.clear();
    text->setText(s);
}

void ControllerWindow::modifyRequest()
{
    int value = this->cp->getValue();

    json j;
    j["attributeTopic"]="89cb0dec-0178-428a-9327-93f1313c3982/Bedroom/TempController/SetTemp";
    j["attribute"]["constraint"]="SetPoint";
    j["attribute"]["timestamp"]=QDateTime::currentSecsSinceEpoch();
    long long dateTime = QDateTime::currentSecsSinceEpoch();
    j["attribute"]["type"]="Integer";
    j["attribute"]["value"]=value;
    QString s = QString::fromStdString(j.dump());
    QByteArray qs = s.toUtf8();

    requestSetpoint.setUrl("http://"+QString(HOSTNAME)+"/api/v1/setAttribute");
    requestSetpoint.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    requestSetpoint.setHeader(QNetworkRequest::ContentLengthHeader,qs.size());
    manager->post(requestSetpoint,qs);
    /*
    j["attributeTopic"]="5d0f6457-8ab4-4ee2-9363-438f2de5b278/Bedroom/TempController/SetTemp";
    manager->post(request,j);
    */
}

void ControllerWindow::onAuthentificationRequestSlot(QNetworkReply *reply, QAuthenticator *authenticator)
{
    authenticator->setUser(CLIENTNAME);
    authenticator->setPassword(PASSWORD);
}

void ControllerWindow::closeEvent(QCloseEvent *event)
{
    for ( auto it : myList )
    {
        it->close();
    }
}
