#include "filemanager_qt.h"

FileManager_qt::FileManager_qt()
{
    //Open file properties
    QString s = ":/properties.txt";
    this->properties = new QFile(s);
    if (!this->properties->open(QIODevice::ReadOnly | QIODevice::Text)){
        Log::printD("Couldn't find file properties");
        return;
    }
    //Read the file properties line by line (since the file has one information per lines)
    QTextStream in(properties);
    while (!in.atEnd()) {
            QString line = this->properties->readLine();
            process_line(line);
        }
    this->properties->close();
}

int FileManager_qt::getPort() const
{
    return port;
}

I_FileManager *I_FileManager::getInstance(){
    return FileManager_qt::getInstance();
}

I_FileManager *FileManager_qt::getInstance()
{
    static FileManager_qt fm = FileManager_qt();
    return &fm;
}

QFile *FileManager_qt::getProperties() const
{
    return properties;
}

QFile *FileManager_qt::getAuthority() const
{
    return authority;
}

QFile *FileManager_qt::getKey() const
{
    return key;
}

void FileManager_qt::process_line(QString line)
{
    QStringList list =line.split("=");
    QString property = list.at(0);
    if(property=="uuid"){
        //our Line keeps the \n character, we don't want it
        int pos = list.at(1).lastIndexOf(QChar('\n'));
        this->uuid=list.at(1).left(pos).toStdString();
    }
    if(property=="hostUri"){
        int pos = list.at(1).lastIndexOf(QChar('\n'));
        string hostFull=list.at(1).left(pos).toStdString();
        pos = hostFull.find_last_of(':');
        int posFirst = hostFull.find_first_of(':');
        this->port = stoi(hostFull.substr(pos+1,hostFull.length()));
        this->host = hostFull.substr(posFirst+3,pos-posFirst-3);
    }
    if(property=="ssl.clientPassword"){
        int pos = list.at(1).lastIndexOf(QChar('\n'));
        this->clientPassword=list.at(1).left(pos).toStdString();
    }
    if(property=="ssl.authorityPassword"){
        int pos = list.at(1).lastIndexOf(QChar('\n'));
        this->authorityPassword=list.at(1).left(pos).toStdString();
    }
    if(property=="persistence"){
        int pos = list.at(1).lastIndexOf(QChar('\n'));
        if(list.at(1).left(pos)=="false"){
            this->persistence=false;
        }
        else {
            this->persistence=true;
        }
    }
    if(property=="ssl.verifyHostname"){
        int pos = list.at(1).lastIndexOf(QChar('\n'));
        if(list.at(1).left(pos)=="false"){
            this->verifyHostname=false;
        }
        else {
            this->persistence=true;
        }
    }
}

string FileManager_qt::getUuid() const
{
    return uuid;
}

string FileManager_qt::getHost() const
{
    return host;
}

bool FileManager_qt::getPersistence() const
{
    return persistence;
}

bool FileManager_qt::getVerifyHostname() const
{
    return verifyHostname;
}
