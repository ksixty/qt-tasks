#include "tasks.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tasks w;
    w.show();
    return a.exec();
}
