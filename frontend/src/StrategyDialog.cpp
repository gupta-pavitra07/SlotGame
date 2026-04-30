#include "StrategyDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include "strategy.h"

StrategyDialog::StrategyDialog(QString strategyText, QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("📊 OPTIMAL STRATEGY");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: #00ffcc;");

    QHBoxLayout* inputLayout = new QHBoxLayout();
    budgetInput = new QLineEdit();
    budgetInput->setPlaceholderText("Enter budget (e.g. 100)");
    budgetInput->setStyleSheet("QLineEdit { background-color: #2a2a40; color: #00ffcc; padding: 10px; border-radius: 5px; font-size: 16px; border: 1px solid #e94560; }");
    
    calcButton = new QPushButton("Calculate");
    calcButton->setStyleSheet("QPushButton { background-color: #e94560; color: white; padding: 10px 20px; font-weight: bold; font-size: 16px; border-radius: 5px; } QPushButton:hover { background-color: #ff4b2b; }");
    
    inputLayout->addStretch();
    inputLayout->addWidget(budgetInput);
    inputLayout->addWidget(calcButton);
    inputLayout->addStretch();

    QFrame* frame = new QFrame();
    frame->setStyleSheet("QFrame { background-color: #1a1a2e; border: 2px solid #00ffcc; border-radius: 15px; } QLabel { border: none; }");
    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

    contentLabel = new QLabel(strategyText);
    contentLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    contentLabel->setWordWrap(true);
    contentLabel->setStyleSheet("font-size: 18px; color: #ffffff; background: transparent; padding: 10px;");

    frameLayout->addWidget(contentLabel);
    frameLayout->setAlignment(Qt::AlignCenter);

    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addLayout(inputLayout);
    layout->addSpacing(20);
    layout->addWidget(frame);
    layout->setAlignment(Qt::AlignTop);

    this->setStyleSheet("background-color: #0b0b16; color: white;");

    connect(calcButton, &QPushButton::clicked, this, &StrategyDialog::calculateStrategy);
}

void StrategyDialog::setStrategyText(const QString& text) {
    contentLabel->setText(text);
}

void StrategyDialog::calculateStrategy() {
    bool ok;
    int budget = budgetInput->text().toInt(&ok);
    if (!ok || budget <= 0) {
        contentLabel->setText("Please enter a valid positive number.");
        return;
    }
    
    std::string greedyStr = Strategy::suggestgreedy(budget);
    std::string dpStr = Strategy::suggestdp(budget);
    
    QString result = QString::fromStdString(greedyStr + "\n------------------------\n\n" + dpStr);
    contentLabel->setText(result);
}