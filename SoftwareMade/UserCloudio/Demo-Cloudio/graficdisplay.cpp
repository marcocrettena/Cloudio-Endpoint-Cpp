#include "graficdisplay.h"
#include <QLine>
#include <cmath>

GraphicDisplay::GraphicDisplay()
{
    setWindowTitle("Grafic Display");
    this->setFixedSize(QSize(1500, 960));
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    this->move(420,10);
    this->setWindowTitle ( QString("Grafic Display") );
    //Charts QT
    this->seriesQTtemp1 = new QLineSeries();
    this->seriesQTtemp1->setName("Bedroom");
    this->seriesQTtemp2 = new QLineSeries();
    this->seriesQTtemp2->setName("Kitchen");
    counterQT=0;
    counterNRF=0;

    this->chartQT = new QChart();
    chartQT->addSeries(seriesQTtemp1);
    chartQT->addSeries(seriesQTtemp2);
    chartQT->setTitle("Measure on QT");
    chartQT->createDefaultAxes();
    chartQT->axes(Qt::Horizontal).first()->setRange(0, 50);
    chartQT->axes(Qt::Vertical).first()->setRange(0, 30);

    viewQT = new QChartView(chartQT);
    viewQT->setRenderHint(QPainter::Antialiasing);
    //Charts nRF
    this->seriesNRFtemp1 = new QLineSeries();
    this->seriesNRFtemp1->setName("Bedroom");
    this->seriesNRFtemp2 = new QLineSeries();
    this->seriesNRFtemp2->setName("Kitchen");
    counterQT=0;
    /*
    this->chartNRF = new QChart();
    chartNRF->addSeries(seriesNRFtemp1);
    chartNRF->addSeries(seriesNRFtemp2);
    chartNRF->setTitle("Measure on NRF");
    chartNRF->createDefaultAxes();
    chartNRF->axes(Qt::Horizontal).first()->setRange(0, 50);
    chartNRF->axes(Qt::Vertical).first()->setRange(0, 30);

    viewNRF = new QChartView(chartNRF);
    viewNRF->setRenderHint(QPainter::Antialiasing);
    */

    //Layout
    QVBoxLayout *myLayout=new QVBoxLayout(this);

    myLayout->addWidget(viewQT);
    //myLayout->addWidget(viewNRF);

    this->show();
}

void GraphicDisplay::setInfo(int owner, double temp1, double temp2, int online, int setPoint)
{
    if(owner==0){
        if(counterQT==51){
            this->seriesQTtemp1->clear();
            this->seriesQTtemp2->clear();
            counterQT=0;
        }
        *this->seriesQTtemp1 << QPointF(counterQT,temp1);
        *this->seriesQTtemp2 << QPointF(counterQT,temp2);
        counterQT++;

    }
    /*
    else{
        if(counterNRF==51){
            this->seriesNRFtemp1->clear();
            this->seriesNRFtemp2->clear();
            counterNRF=0;
        }
        *this->seriesNRFtemp1 << QPointF(counterNRF,temp1);
        *this->seriesNRFtemp2 << QPointF(counterNRF,temp2);
        counterNRF++;
    }
    */
    repaint();
}


void GraphicDisplay::paintEvent(QPaintEvent *)
{

}
