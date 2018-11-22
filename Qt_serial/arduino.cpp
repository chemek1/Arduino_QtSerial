#include "arduino.h"
#include "ui_arduino.h"

arduino::arduino(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::arduino)
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    ui->setupUi(this);
    serial=new QSerialPort;
    int ret=connect_arduino();
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< arduino_port_name;
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<arduino_port_name;
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(serial,SIGNAL(readyRead()),this,SLOT(read_from_arduino()));
}

arduino::~arduino()
{
    if(!close_arduino())
        qDebug() << "arduino closed properly";
    else
        qDebug() << "problem when closing arduino ";

    delete serial;
    qDebug() << "serial object destroyed";
    delete ui;
    qDebug() << "Ui object destroyed";

}

int arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name=serial_port_info.portName();
            }
        }
    }

    qDebug() << "arduino_port_name is :" << arduino_port_name;

    if(arduino_is_available){
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite)){
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

int arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}

int arduino::write_to_arduino()
{
    if(serial->write(data) < 0)
        return -1;
    return 0;
}

void arduino::read_from_arduino()
{
    data=serial->readAll();
    arduino::update_label();

}

void arduino::update_label()
{
    qDebug()<< "received from arduino :" << data;
    ui->label->setText(data);

}

void arduino::on_pushButton_clicked()
{
    data="";
    data.insert(0,'1');
    if(write_to_arduino() < 0)
        qDebug()<<"problem sending data :"<<data;
    else
        qDebug() << "data sent : "<< data;

}

void arduino::on_pushButton_2_clicked()
{
    data="";
    data.insert(0,'0');
    if(write_to_arduino() < 0)
        qDebug()<<"problem sending data :"<<data;
    else
         qDebug() << "data sent : "<< data;

}
