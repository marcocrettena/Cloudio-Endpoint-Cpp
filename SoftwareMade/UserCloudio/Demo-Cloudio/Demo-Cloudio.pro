QT       += core gui widgets network
QT += charts

TARGET = RequestCloudioDemo
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    graficdisplay.cpp \
        main.cpp \
        controllerwindow.cpp \
    digitaldisplay.cpp \
    controlpanel.cpp \
    displaybase.cpp

HEADERS += \
        controllerwindow.h \
    digitaldisplay.h \
    controlpanel.h \
    displaybase.h \
    graficdisplay.h \
    json.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
