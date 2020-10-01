#ifndef FILEMANAGER_QT_H
#define FILEMANAGER_QT_H

#include <QFile>
#include <QTextStream>
#include <iostream>

#include "Interface/i_logger.h"
#include "Interface/i_filemanager.h"

using namespace std;

class FileManager_qt : public I_FileManager
{
public:
    static I_FileManager * getInstance();
    QFile *getProperties() const;
    QFile *getAuthority() const;
    QFile *getKey() const;
    void process_line(QString line);
    string getUuid() const;
    string getHost() const;
    int getPort() const;
    bool getPersistence() const;
    bool getVerifyHostname() const;

protected:
    FileManager_qt();
protected:
    QFile* properties;
    QFile* authority;
    QFile* key;
    string uuid;
    string host;
    int port;
    string clientPassword;
    string authorityPassword;
    bool persistence;
    bool verifyHostname;
};

#endif // FILEMANAGER_QT_H
