#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql \
    quick
QT       += core gui sql
QT       += core gui charts
QT       += core gui multimedia

QT += axcontainer
QT += printsupport
QT += widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    DuMessengerSocket.cpp \
    chat.cpp \
    connection.cpp \
    dumessengerconnectiondialog.cpp \
    dumessengerserver.cpp \
    employe.cpp \
    equipement.cpp \
        main.cpp \
        mainwindow.cpp \
    qrcode.cpp \
    stat_combo.cpp

HEADERS += \
    DuMessengerSocket.h \
    chat.h \
    connection.h \
    dumessengerconnectiondialog.h \
    dumessengerserver.h \
    employe.h \
    equipement.h \
        mainwindow.h \
    qrcode.h \
    stat_combo.h

FORMS += \
        chat.ui \
        dumessengerconnectiondialog.ui \
        mainwindow.ui \
        stat_combo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

STATECHARTS +=

DISTFILES +=
