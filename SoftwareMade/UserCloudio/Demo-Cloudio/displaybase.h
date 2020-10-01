#ifndef DISPLAYBASE_H
#define DISPLAYBASE_H
#include <QWidget>

class DisplayBase : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayBase(QWidget *parent = nullptr);

public slots:
    virtual void setInfo(int owner, double temp1, double temp2, int online, int setPoint)=0;
};

#endif // DISPLAYBASE_H
