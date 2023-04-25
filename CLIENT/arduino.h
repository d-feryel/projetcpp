#ifndef ARDUINO_H
#define ARDUINO_H
#include <QByteArray>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <qdebug.h>


class Arduino
{
public:
    Arduino();
    int connectArduino();
    int closeArduino();
    int writeToArduino(QByteArray);
    QByteArray readFromArduino();
    QSerialPort* getSerial();
    QString getArduinoPortName();
private:
    QSerialPort * serial;
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;
    QString arduinoPortName;
    bool arduinoIsAvailable;
    QByteArray data;


};

#endif // ARDUINO_H
