QT       += core gui sql charts
QT+= sql
QT+= network
QT += printsupport
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11
  CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DuMessengerSocket.cpp \
    chat.cpp \
    connection.cpp \
    dumessengerconnectiondialog.cpp \
    dumessengerserver.cpp \
    employe.cpp \
    main.cpp \
    mainwindow.cpp \
    stat_combo.cpp
QMAKE_CFLAGS += -std =gnu++11

HEADERS += \
    DuMessengerSocket.h \
    chat.h \
    connection.h \
    dumessengerconnectiondialog.h \
    dumessengerserver.h \
    employe.h \
    mainwindow.h \
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
