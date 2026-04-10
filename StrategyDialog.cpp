#include "StrategyDialog.h"
#include <QVBoxLayout>
#include <QLabel>

StrategyDialog::StrategyDialog(QString strategyText, QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("📊 Strategy Suggestion");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold;");

    QLabel* text = new QLabel(strategyText);
    text->setAlignment(Qt::AlignCenter);

    layout->addWidget(title);
    layout->addWidget(text);

    setLayout(layout);
    setWindowTitle("Strategy");
    resize(300, 150);
}