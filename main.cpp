#include <QApplication>
#include "StartWindow.h"
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    srand(time(0));

    a.setStyleSheet(R"(

    QMainWindow, QDialog, QWidget {
        background-color: #1e1e2f;
        color: white;
    }

    QLabel {
        color: white;
        font-size: 16px;
    }

    QPushButton {
        background-color: #ff3c3c;
        color: white;
        border-radius: 10px;
        padding: 10px;
        font-size: 16px;
    }

    QPushButton:hover {
        background-color: #ff5c5c;
    }

    QLineEdit {
        background-color: #2b2b3c;
        color: white;
        padding: 10px;
        border-radius: 8px;
        font-size: 16px;
    }

    QTableWidget {
        background-color: #0707e0;
        color: white;
        border-radius: 10px;
    }

    QHeaderView::section {
        background-color: #ff3cd1;
        color: white;
        padding: 5px;
    }

    )");

    StartWindow w;
    w.setFixedSize(800, 500);
    w.show();

    return a.exec();

    
}