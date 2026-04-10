#include "StartWindow.h"
#include "MainWindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("🎮 Welcome to Slot Game");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold;");

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter your name");

    balanceInput = new QLineEdit();
    balanceInput->setPlaceholderText("Enter starting balance");

    QPushButton* startBtn = new QPushButton("Start Game");

    layout->addWidget(title);
    layout->addWidget(nameInput);
    layout->addWidget(balanceInput);
    layout->addWidget(startBtn);

    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 30, 30, 30);

    connect(startBtn, &QPushButton::clicked, this, &StartWindow::startGame);

    setLayout(layout);
    setWindowTitle("Start");

    this->setFixedSize(800, 500);
}

void StartWindow::startGame()
{
    QString name = nameInput->text();
    double balance = balanceInput->text().toDouble();

    if (name.isEmpty() || balance <= 0)
        return;

    MainWindow* game = new MainWindow(name, balance);
    game->show();

    this->close();
}