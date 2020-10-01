#include "ssl_qt.h"
#include "Interface/i_filemanager.h"
#include "Interface/i_logger.h"
#include "QFile"

SSL_qt* SSL_qt::ssl=nullptr;

SSL_qt::SSL_qt()
{
    socket= new QSslSocket();
    //These connects were just here for tests
    /*
    connect(socket,&QSslSocket::peerVerifyError,this,&SSL_qt::someslot);
    connect(socket,&QSslSocket::encrypted,this,&SSL_qt::someslot);
    */
    init_SSL();
}

SSL_qt::~SSL_qt()
{
    if(socket!=nullptr){
        delete socket;
    }
}

void SSL_qt::init_SSL()
{
    //Add Peer name
    QString host = QString::fromStdString(I_FileManager::getInstance()->getHost());
    socket->setPeerVerifyName("rabbit");

    //Give all the certificates needed
    QList<QSslCertificate> certy = QSslCertificate::fromPath(":/caCertificate.pem");
    socket->setCaCertificates(certy);
    socket->setPrivateKey(":/ClientKey.pem");
    socket->setLocalCertificate(":/ClientCertificate.cer");

    //Gestion of error, not made
    /* Attempt to not verify the Peer Identity, not working however with the threads attempt (signal problems), can maybe work now.
    QList<QSslError> listSslError;
    QSslError selfSigned = QSslError(QSslError::SelfSignedCertificate);
    QSslError selfSignedChain = QSslError(QSslError::SelfSignedCertificateInChain);
    QSslError untrusted = QSslError(QSslError::CertificateUntrusted);
    listSslError.push_front(selfSigned);
    listSslError.push_front(selfSignedChain);
    listSslError.push_front(untrusted);
    ssl->socket->ignoreSslErrors(listSslError);

    //Last chance to test without verifying certificates
    ssl->socket->setPeerVerifyMode(QSslSocket::QueryPeer);
    */

    //Setup connection
    socket->connectToHostEncrypted(host,I_FileManager::getInstance()->getPort());

    if(!socket->waitForEncrypted(5000))
    {
        Log::printD(socket->errorString().toStdString());
    }
}

void SSL_qt::someslot()
{
    Log::printD("catch handshake result");
}

SSL_qt *SSL_qt::getInstance()
{
    if(ssl==nullptr){
        ssl =new SSL_qt();
    }
    return ssl;
}

QSslSocket *SSL_qt::getSocket() const
{
    return ssl->socket;
}
