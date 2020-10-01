#include <QtGlobal>
#include <qdatetime.h>
#include "thread-default.h"
#include "Interface/mutex.h"
#include "resourcefactory.h"

//static
ResourceFactory * ResourceFactory::getInstance()
{
    return ResourceFactoryPort::getInstance();
}

ResourceFactory *ResourceFactoryPort::getInstance()
{
    static ResourceFactoryPort rfp = ResourceFactoryPort();
    return &rfp;
}

Thread *ResourceFactoryPort::createThread(ThreadEntryPointProvider * pProvider,Thread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    ThreadDefault* thread = new ThreadDefault(pProvider, entryMethod, threadName, stackSize);
    return thread;
}

Mutex *ResourceFactoryPort::createMutex()
{
    Mutex* mutex = Mutex::create();
    return mutex;
}

long long ResourceFactoryPort::getTimestamp()
{
    long long retVal = QDateTime::currentMSecsSinceEpoch();
    retVal = retVal /1000;
    return retVal;
}
