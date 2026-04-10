#include "ResultDialog.h"
#include <QVBoxLayout>
#include <QLabel>

QString getSymbolEmoji(const std::string& symbol)
{
    if (symbol == "CHERRY") return "🍒";
    if (symbol == "STAR") return "⭐";
    if (symbol == "DIAMOND") return "💎";
    if (symbol == "BELL") return "🔔";
    if (symbol == "7") return "7️⃣";

    return "?";
}

ResultDialog::ResultDialog(QString result, double reward, double balance, QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();

    QStringList parts = result.split(" | ");

    QString display =
        getSymbolEmoji(parts[0].toStdString()) + "     " +
        getSymbolEmoji(parts[1].toStdString()) + "     " +
        getSymbolEmoji(parts[2].toStdString());

    QLabel* symbolLabel = new QLabel(display);
    symbolLabel->setAlignment(Qt::AlignCenter);
    symbolLabel->setStyleSheet("font-size: 80px; font-weight: bold;");

    QLabel* resultText = new QLabel("🎰 RESULT : " + result);
    resultText->setAlignment(Qt::AlignCenter);

    QLabel* winLabel;
    if (reward > 0)
    {
        winLabel = new QLabel("🎉 YOU WIN ₹" + QString::number(reward));
        winLabel->setStyleSheet("color: #00ff99; font-size: 26px;");
    }
    else
    {
        winLabel = new QLabel("❌ YOU LOST");
        winLabel->setStyleSheet("color: red; font-size: 26px;");
    }
    winLabel->setAlignment(Qt::AlignCenter);

    QLabel* balanceLabel = new QLabel("💰 BALANCE : ₹" + QString::number(balance));
    balanceLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(symbolLabel);
    layout->addWidget(resultText);
    layout->addWidget(winLabel);
    layout->addWidget(balanceLabel);

    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(25);
    layout->setContentsMargins(40, 40, 40, 40);

    setLayout(layout);
    setWindowTitle("RESULT");

    this->setFixedSize(800, 500);
}