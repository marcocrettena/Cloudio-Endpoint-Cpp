#ifndef LOGGER_qt_H
#define LOGGER_qt_H

#include <iostream>
#include <QtDebug>

#include "Interface/i_logger.h"

using namespace std;

class Logger_qt : public I_Logger
{
public:
    virtual ~Logger_qt(){}
    static I_Logger * getInstance();
    void logPrint(const char* message);
    void logPrint(string message);
};

#endif // LOGGER_H
