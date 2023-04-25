#include "arduino.h"
#include <QByteArray>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <qdebug.h>

Arduino::Arduino()
{
    data ="";
    arduinoPortName ="";
    arduinoIsAvailable =false;
    serial=new QSerialPort;
}

int Arduino::connectArduino()
{
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id && serialPortInfo.productIdentifier() == arduino_uno_producy_id){
                arduinoIsAvailable = true;
                arduinoPortName = serialPortInfo.portName();
            }
        }
    }
    qDebug() << "arduinoPortName is :" << arduinoPortName;
    if(arduinoIsAvailable){
        serial->setPortName("COM4");
        if(serial->open(QSerialPort::ReadWrite)){
            qDebug() << "yo";
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
        return 1;
    }
    return -1;
}

int Arduino::closeArduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 0;
}

int Arduino::writeToArduino(QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);
    }
    else{
        qDebug() << "couldn't write to serial!";
    }
}

QByteArray Arduino::readFromArduino()
{
    if(serial->isReadable()){
        data = serial->readAll();
        return data;
    }
}

QSerialPort *Arduino::getSerial()
{
    return serial;
}

QString Arduino::getArduinoPortName()
{
    return arduinoPortName;
}


