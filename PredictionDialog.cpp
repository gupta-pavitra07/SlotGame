#include "PredictionDialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

PredictionDialog::PredictionDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("🧠 Make Prediction");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 26px; font-weight: bold;");

    typeBox = new QComboBox();
    typeBox->addItems({"EXACT", "SYMBOL", "PATTERN"});

    symbolBox = new QComboBox();
    symbolBox->addItems({"CHERRY", "STAR", "DIAMOND", "BELL", "7", "ALL", "PAIR"});

    input2 = new QLineEdit();
    input3 = new QLineEdit();

    input2->setPlaceholderText("Symbol 2 (Exact only)");
    input3->setPlaceholderText("Symbol 3 (Exact only)");

    amountInput = new QLineEdit();
    amountInput->setPlaceholderText("Enter amount");

    QPushButton* submit = new QPushButton("Add Prediction");

    layout->addWidget(title);
    layout->addWidget(typeBox);
    layout->addWidget(symbolBox);
    layout->addWidget(input2);
    layout->addWidget(input3);
    layout->addWidget(amountInput);
    layout->addWidget(submit);

    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 30, 30, 30);

    connect(typeBox, &QComboBox::currentTextChanged,
            this, &PredictionDialog::updateUI);

    connect(submit, &QPushButton::clicked, [=]() {

        prediction.amount = amountInput->text().toDouble();

        QString s1 = symbolBox->currentText().toUpper();
        QString s2 = input2->text().trimmed().toUpper();
        QString s3 = input3->text().trimmed().toUpper();

        if (typeBox->currentText() == "EXACT")
        {
            prediction.type = EXACT;
            prediction.s1 = s1.toStdString();
            prediction.s2 = s2.toStdString();
            prediction.s3 = s3.toStdString();
        }
        else if (typeBox->currentText() == "SYMBOL")
        {
            prediction.type = SYMBOL;
            prediction.symbol = s1.toStdString();
        }
        else
        {
            prediction.type = PATTERN;
            prediction.pattern = s1.toStdString();
        }

        accept();
    });

    setLayout(layout);
    setWindowTitle("Prediction");

    this->setFixedSize(800, 500);

    updateUI();
}
void PredictionDialog::updateUI()
{
    QString type = typeBox->currentText();

    if (type == "EXACT")
    {
        input2->show();
        input3->show();
    }
    else
    {
        input2->hide();
        input3->hide();
    }
}
Prediction PredictionDialog::getPrediction()
{
    return prediction;
}