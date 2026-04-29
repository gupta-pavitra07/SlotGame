#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w("Pavitra", 680, "Thala@81", 3, false);
    w.show();

    return a.exec();
}
