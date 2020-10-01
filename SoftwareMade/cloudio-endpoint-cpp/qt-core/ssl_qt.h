#ifndef SSL_QT_H
#define SSL_QT_H

#include <qsslsocket.h>
#include <qsslerror.h>

/**
 * @brief The SSL_qt class
 * To do a SSL protocol, QT provides the class QSslSocket
 * The SSL_qt will so provide all the clientMqtt instance needs to do the SSL protocol
 */
class SSL_qt : public QObject
{
    Q_OBJECT
public:
    QSslSocket *getSocket() const;
    static SSL_qt * getInstance();
protected:
    SSL_qt();
    ~SSL_qt();
    // I_SSL interface
protected:
    void init_SSL();
private:
    QSslSocket* socket;
    static SSL_qt* ssl;
private slots:
    void someslot();
};

#endif // SSL_QT_H
