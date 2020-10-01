#ifndef XF_INTERFACE_RESOURCE_FACTORY_H
#define XF_INTERFACE_RESOURCE_FACTORY_H

#include "mutex.h"
#include "thread.h"

/**
 * @brief Responsible to create and return XF resources.
 *
 * The XF resource factory provides instances of following classes
 *  - Dispatcher
 *  - Thread
 *  - Mutex
 *
 * The XFResourceFactory::getInstance() method needs to be implemented
 * in the class realizing this interface.
 *
 */
class ResourceFactory
{
public:
    static ResourceFactory * getInstance();   ///< Returns a pointer to the unique instance of the XF resource factory.

    /**
     * @brief Creates a new Thread.
     * @param pProvider The instance providing the entry method.
     * @param entryMethod The method to by called by the new thread.
     * @param threadName The name of the thread.
     * @param stackSize The stack size of the thread.
     * @return Pointer to new thread
     *
     * The method may return null in case there is no OS present.
     */
    virtual Thread * createThread( ThreadEntryPointProvider * pProvider,
                                   Thread::EntryMethodBody entryMethod,
                                   const char * threadName,
                                   const uint32_t stackSize = 0) = 0;
    /**
     * @brief Returns a new mutex.
     * @return Pointer to new mutex.
     */
    virtual Mutex * createMutex() = 0;

    virtual long long getTimestamp() = 0;

    virtual ~ResourceFactory() = default;

protected:
    ResourceFactory() = default;
};

#endif // XF_INTERFACE_RESOURCE_FACTORY_H
