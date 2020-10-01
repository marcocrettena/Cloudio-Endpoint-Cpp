#include "i_logger.h"


void Log::printD(const char* message)
{
    I_Logger::getInstance()->logPrint(message);
}

void Log::printD(string message)
{
    I_Logger::getInstance()->logPrint(message);
}
