#ifndef XF_INTERFACE_THREAD_H
#define XF_INTERFACE_THREAD_H

#include "stdint.h"

typedef enum
{
    THREAD_PRIO_UNKNOWN = 0,
    THREAD_PRIO_LOW = 5,
    THREAD_PRIO_NORMAL = 10,
    THREAD_PRIO_HIGH = 15,
    THREAD_PRIO_MAX = 20
} ThreadPriority;


/**
 * @brief Interface to be implemented by the class providing the thread entry method.
 */
class ThreadEntryPointProvider
{
public:
    virtual ~ThreadEntryPointProvider() = default;
protected:
    ThreadEntryPointProvider() = default;
};

/**
 * @brief Interface for a Thread.
 *
 * Thread interface representing the instance executing the behavior. In an OS less XF
 * (hence an IDF), usually this class is not needed. In an XF interfacing an OS,
 * multiple instances can be made, each interfacing the real OS thread.
 *
 * Thread instances can be created using the ResourceFactory instance.
 *
 * The XF assumes that the Thread is in suspend state after creation. Automatically
 * starting the thread after creation may lead to unwanted behavior!
 */
class Thread
{
public:
    virtual ~Thread() = default;

    typedef void (ThreadEntryPointProvider::*EntryMethodBody)(const void *);  ///< Prototype of method to be executed by the thread.

    virtual void start() = 0;                                                   ///< Starts the thread.
    virtual void stop() = 0;                                                    ///< Requests the thread to stop execution.

    virtual void setPriority(ThreadPriority priority) = 0;                    ///< Set the thread priority.
    virtual ThreadPriority getPriority() const = 0;                           ///< Returns the thread priority.

    virtual void delay(uint32_t milliseconds) = 0;                              ///< Causes the thread to sleep (for the given milliseconds).
    virtual bool getIsRunning()=0;
protected:

    Thread() = default;
};

#endif // XF_INTERFACE_THREAD_H
