#include "ResultDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>


ResultDialog::ResultDialog(QString result, double reward, double balance, QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();

    QFrame* frame = new QFrame();
    frame->setStyleSheet("QFrame { background-color: #1a1a2e; border: 3px solid #e94560; border-radius: 20px; } QLabel { border: none; }");
    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

    QStringList parts = result.split(" | ");

    QString display = parts[0] + "     " + parts[1] + "     " + parts[2];

    QLabel* symbolLabel = new QLabel(display);
    symbolLabel->setAlignment(Qt::AlignCenter);
    symbolLabel->setStyleSheet("font-size: 100px; font-weight: bold; background: transparent;");

    QLabel* resultText = new QLabel("🎰 RESULT : " + result);
    resultText->setAlignment(Qt::AlignCenter);
    resultText->setStyleSheet("font-size: 24px; color: #00ffcc; font-weight: bold; background: transparent;");

    QLabel* winLabel;
    if (reward > 0)
    {
        winLabel = new QLabel("🎉 JACKPOT! YOU WIN " + QString::number(reward) + " COINS");
        winLabel->setStyleSheet("color: #00ff99; font-size: 36px; font-weight: bold; background: transparent;");
    }
    else
    {
        winLabel = new QLabel("❌ BETTER LUCK NEXT TIME");
        winLabel->setStyleSheet("color: #ff3c3c; font-size: 30px; font-weight: bold; background: transparent;");
    }
    winLabel->setAlignment(Qt::AlignCenter);

    QLabel* balanceLabel = new QLabel("💰 NEW BALANCE : " + QString::number(balance) + " COINS");
    balanceLabel->setAlignment(Qt::AlignCenter);
    balanceLabel->setStyleSheet("font-size: 24px; color: #f0f0f0; background: transparent;");

    frameLayout->addWidget(symbolLabel);
    frameLayout->addWidget(resultText);
    frameLayout->addWidget(winLabel);
    frameLayout->addWidget(balanceLabel);
    frameLayout->setAlignment(Qt::AlignCenter);
    frameLayout->setSpacing(25);
    frameLayout->setContentsMargins(40, 40, 40, 40);

    layout->addWidget(frame);
    layout->setAlignment(Qt::AlignCenter);

    setLayout(layout);
    setWindowTitle("SPIN RESULT");

    this->setFixedSize(800, 500);
}