#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMainWindow>
#include <QDebug>
namespace Ui {
class arduino;
}

class arduino : public QMainWindow
{
    Q_OBJECT

public:
    explicit arduino(QWidget *parent = nullptr);
    ~arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino();


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void read_from_arduino();
    void update_label();

private:
    Ui::arduino *ui;
    QSerialPort * serial;
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;

};

#endif // ARDUINO_H
