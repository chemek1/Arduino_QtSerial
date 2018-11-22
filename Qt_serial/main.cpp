#include "arduino.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    arduino w;
    w.show();

    return a.exec();
}
