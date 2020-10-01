#ifndef XF_PORT_IDF_QT_RESOURCE_FACTORY_H
#define XF_PORT_IDF_QT_RESOURCE_FACTORY_H

/** @ingroup port_idf_qt
 *  @{
 */

#include "Interface/resourcefactory.h"

/**
 * @brief XFResourceFactoryPort implementation for the IDF Qt port.
 */
class ResourceFactoryPort : public ResourceFactory
{
public:
    virtual ~ResourceFactoryPort() {}

    static ResourceFactory * getInstance();            ///< Returns a pointer to the unique instance of the XF resource factory.

    virtual Thread * createThread(  ThreadEntryPointProvider * pProvider,
                                    Thread::EntryMethodBody entryMethod,
                                    const char * threadName,
                                    const uint32_t stackSize = 0);                         ///< Creates and returns a new thread.
    virtual Mutex * createMutex();                                                     ///< Creates and returns a new mutex.

    long long getTimestamp();
protected:
    ResourceFactoryPort() {}
};

/** @} */ // end of port_idf_qt group
#endif // XF_PORT_IDF_QT_RESOURCE_FACTORY_H
