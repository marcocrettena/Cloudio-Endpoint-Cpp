#ifndef XF_THREAD_DEFAULT_QT_H
#define XF_THREAD_DEFAULT_QT_H

#include <QThread>
#include <stdint.h>
#include "Interface/thread.h"

/** @ingroup port_default_qt
 *  @{
 */

/**
 * @brief Default thread implementation for the IDF Qt port
 */
class ThreadDefault : public QThread,
                      public Thread
{
    friend class ResourceFactoryPort;

    // interface::Thread interface implementation
public:
    virtual void start();
    virtual void stop();

    virtual void setPriority(ThreadPriority priority);
    virtual ThreadPriority getPriority() const;

    virtual void delay(uint32_t milliseconds);

    virtual bool getIsRunning();

protected:
    /**
     * @brief Protected XFThreadDefault constructor
     * @param pProvider Instance providing the method to be executed by the thread.
     * @param entryMethod Method to be executed by the Thread (usually containing a infinite loop).
     * @param threadName Name of the thread.
     * @param stackSize Stack size of the thread.
     *
     * Constructor is protected because only the XFResourceFactory interface
     * based class (XFResourceFactoryPort) is allowed to created threads.
     */
    ThreadDefault(ThreadEntryPointProvider * pProvider,
                  Thread::EntryMethodBody entryMethod,
                  const char * threadName,
                  const uint32_t stackSize = 0);

    // QThread interface implementation
protected:
    virtual void run();                                                 ///< Override of the QThread run method.

protected:
    ThreadEntryPointProvider * _pEntryMethodProvider;      ///< Pointer to object providing the entry method.
    Thread::EntryMethodBody _entryMethod;                  ///< Entry method to be called/executed by the thread.
    bool isRunning;

};

/** @} */ // end of port_default_qt group
#endif // XF_THREAD_DEFAULT_QT_H
