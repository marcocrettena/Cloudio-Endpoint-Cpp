#include "logger_qt.h"

I_Logger * I_Logger::getInstance(){
    return Logger_qt::getInstance();
}

I_Logger *Logger_qt::getInstance()
{
    static Logger_qt log = Logger_qt();
    return &log;
}

void Logger_qt::logPrint(const char* message)
{
    qDebug()<<message;
}

void Logger_qt::logPrint(string message)
{
    const char* msg = message.c_str();
    qDebug()<<msg;
}
