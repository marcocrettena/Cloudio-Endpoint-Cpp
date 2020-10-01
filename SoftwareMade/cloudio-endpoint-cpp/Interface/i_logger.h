#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

using namespace std;

/**
 * @brief The Logger class
 * Abstraction layer to print some messages somewhere for debugging. Could be use to send MQTT messages to the /@log topic to the broker
 */
class I_Logger
{
public:
    static I_Logger * getInstance();
    virtual void logPrint(const char* message)=0;
    virtual void logPrint(string message)=0;
    virtual ~I_Logger() = default;
};

class Log{
public:
    static void printD(const char* message);
    static void printD(string message);
};

#endif // LOGGER_H
