#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);

private slots:
    void startGame();

private:
    QLineEdit* nameInput;
    QLineEdit* balanceInput;
    QPushButton* startButton;
};

#endif