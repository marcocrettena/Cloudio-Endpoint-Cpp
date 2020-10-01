QT += core
QT += mqtt network widgets

TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle

SOURCES += \
    Interface/i_logger.cpp \
    Utility/queuemessage.cpp \
    Utility/topic.cpp \
    captorpoll.cpp \
        main.cpp \
    EndpointController/endpointcontroller.cpp \
    EndpointController/endpointfactory.cpp \
    EndpointStructure/endpoint.cpp \
    EndpointStructure/node.cpp \
    EndpointStructure/object.cpp \
    EndpointStructure/attribute.cpp \
    Utility/message.cpp \
    Interface/i_mqtt.cpp \
    qt-core/logger_qt.cpp \
    qt-core/filemanager_qt.cpp \
    qt-core/mutex-default.cpp \
    qt-core/resourcefactory.cpp \
    qt-core/thread-default.cpp \
    qt-core/mqtt.cpp \
    qt-core/ssl_qt.cpp

HEADERS += \
    EndpointController/endpointcontroller.h \
    EndpointController/endpointfactory.h \
    EndpointStructure/node.h \
    EndpointStructure/object.h \
    EndpointStructure/attribute.h \
    EndpointStructure/endpoint.h \
    Interface/i_logger.h \
    Utility/json.hpp \
    Utility/message.h \
    Interface/i_mqtt.h \
    Interface/mutex.h \
    Interface/resourcefactory.h \
    Interface/thread.h \
    Interface/i_filemanager.h \
    Utility/queuemessage.h \
    Utility/topic.h \
    captorpoll.h \
    qt-core/filemanager_qt.h \
    qt-core/logger_qt.h \
    qt-core/resourcefactory.h \
    qt-core/thread-default.h \
    qt-core/mutex-default.h \
    qt-core/mqtt_qt.h \
    qt-core/ssl_qt.h

RESOURCES += \
    ressources/ressources.qrc


