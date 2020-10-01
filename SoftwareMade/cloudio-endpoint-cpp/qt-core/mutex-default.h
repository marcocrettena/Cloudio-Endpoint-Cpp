#ifndef XF_MUTEX_DEFAULT_QT_H
#define XF_MUTEX_DEFAULT_QT_H

#include <stdint.h>
#include <QMutex>
#include "Interface/mutex.h"

/** @ingroup port_default_qt
 *  @{
 */

/**
 * @brief Default Qt implementation for the XFMutex interface.
 */
class MutexDefault : public Mutex
{
    friend class Mutex;
public:
    static Mutex* create();
    virtual ~MutexDefault() = default;

    virtual void lock();
    virtual void unlock();

    virtual bool tryLock(int32_t timeout = 0);

protected:
    MutexDefault() = default;    ///< Do not allow to directly create an object of this class. Call XFMutex::create() instead.

protected:
    QMutex _mutex;              ///< The real mutex.
};

/** @} */ // end of port_default_qt group
#endif // MUTEX_DEFAULT_QT_H
