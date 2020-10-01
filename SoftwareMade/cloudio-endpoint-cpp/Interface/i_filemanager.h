#ifndef I_FILEMANAGER_H
#define I_FILEMANAGER_H

#include <iostream>

using namespace std;

class Cloudio_Endpoint;
class EndpointController;

/**
 * @brief The FileManager class
 * Some informations will be provided in some files for easier configuration, this class read the important informations in the different files
 * and provide some methods to give these informations
 * For the moment, this class does nothing with the certificate even if it was planned at first.
 * This class can be replaced by a .h file with all the #define we need for the application, it will be easier to implement than one FileManager for each environnement
 */
class I_FileManager
{
    friend Cloudio_Endpoint;
    friend EndpointController;
public:
    static I_FileManager * getInstance();
    virtual ~I_FileManager() = default;
    virtual string getUuid() const=0;
    virtual string getHost() const=0;
    virtual int getPort() const=0;
    //These two functions aren't used by the application for the moment
    virtual bool getPersistence() const=0;
    /**
     * @brief getVerifyHostname
     * Not used by the application for the moment
     * @return bool which indicates if the hostname must be verified
     */
    virtual bool getVerifyHostname() const=0;
protected:
    I_FileManager() = default;
};

#endif // I_FILEMANAGER_H
