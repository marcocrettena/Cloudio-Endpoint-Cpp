#include <assert.h>
#include <string.h>
#include "thread-default.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif

void ThreadDefault::start()
{
    QThread::start();
}

void ThreadDefault::stop()
{
    QThread::terminate();
    QThread::wait();
    isRunning=false;
}

void ThreadDefault::setPriority(ThreadPriority priority)
{
    QThread::Priority qPriority;
    switch(priority){
        case THREAD_PRIO_UNKNOWN :
        qPriority=QThread::IdlePriority;
        break;
        case THREAD_PRIO_LOW :
        qPriority=QThread::LowPriority;
        break;
        case THREAD_PRIO_NORMAL :
        qPriority=QThread::NormalPriority;
        break;
        case THREAD_PRIO_HIGH :
        qPriority=QThread::HighPriority;
        break;
        case THREAD_PRIO_MAX :
        qPriority=QThread::HighestPriority;
        break;
    }
    QThread::setPriority(qPriority);
}

ThreadPriority ThreadDefault::getPriority() const
{
    QThread::Priority priority=this->QThread::priority();
    switch(priority){
        case QThread::IdlePriority :
        return THREAD_PRIO_UNKNOWN ;

        case  QThread::LowPriority :
        return THREAD_PRIO_LOW;

        case  QThread::NormalPriority :
        return THREAD_PRIO_NORMAL ;

        case QThread::HighPriority:
        return  THREAD_PRIO_HIGH ;

        case QThread::HighestPriority:
        return  THREAD_PRIO_MAX ;
    }
}

void ThreadDefault::delay(uint32_t milliseconds)
{
    QThread::sleep(milliseconds);
}

bool ThreadDefault::getIsRunning()
{
    return this->isRunning;
}

ThreadDefault::ThreadDefault(ThreadEntryPointProvider *pProvider, Thread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    this->_entryMethod=entryMethod;
    this->_pEntryMethodProvider=pProvider;
}

void ThreadDefault::run()
{
    isRunning=true;
    (this->_pEntryMethodProvider->*this->_entryMethod)(this);
}
