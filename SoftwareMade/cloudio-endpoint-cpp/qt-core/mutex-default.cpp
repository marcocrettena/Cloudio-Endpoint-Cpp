#include <assert.h>

#include "mutex-default.h"

Mutex *Mutex::create()
{
    return new MutexDefault;
}

void MutexDefault::lock()
{
    this->_mutex.lock();
}

void MutexDefault::unlock()
{
    this->_mutex.unlock();
}

bool MutexDefault::tryLock(int32_t timeout)
{
    this->_mutex.tryLock(timeout);
}


