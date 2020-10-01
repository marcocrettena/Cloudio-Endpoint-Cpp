#ifndef GRAFICDISPLAY_H
#define GRAFICDISPLAY_H


#include <QWidget>
#include <QPainter>
#include <QTime>
#include <displaybase.h>

#include <QtCharts>

using namespace QtCharts;

class GraphicDisplay : public DisplayBase
{
    Q_OBJECT
public:
    GraphicDisplay();
public slots:
    void setInfo(int owner, double temp1, double temp2, int online, int setPoint);

private:
    QLineSeries* seriesQTtemp1;
    QLineSeries* seriesQTtemp2;
    QLineSeries* seriesNRFtemp1;
    QLineSeries* seriesNRFtemp2;

    QChart* chartQT;
    QChart* chartNRF;

    QChartView* viewQT;
    QChartView* viewNRF;
    int counterQT;
    int counterNRF;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // GRAFICDISPLAY_H
