#include "PredictionDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

PredictionDialog::PredictionDialog(double currentBalance, QWidget *parent)
    : QDialog(parent), maxBalance(currentBalance)
{
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("🧠 Make Prediction");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 32px; font-weight: bold; color: #00ffcc;");

    QString btnStyle = "QPushButton { background-color: #2a2a40; color: white; padding: 10px; border-radius: 5px; font-size: 18px; border: 2px solid #333; } "
                       "QPushButton:hover { background-color: #404060; } "
                       "QPushButton:checked { background-color: #e94560; border: 2px solid #00ffcc; font-weight: bold; }";


    QLabel* typeLabel = new QLabel("Select Prediction Type:");
    typeLabel->setStyleSheet("font-size: 16px; color: #aaa;");
    QHBoxLayout* typeLayout = new QHBoxLayout();
    QStringList types = {"EXACT", "SYMBOL", "PATTERN"};
    for (const QString& t : types) {
        QPushButton* btn = new QPushButton(t);
        btn->setStyleSheet(btnStyle);
        btn->setCheckable(true);
        if (t == "EXACT") btn->setChecked(true);
        typeButtons.push_back(btn);
        typeLayout->addWidget(btn);
        connect(btn, &QPushButton::clicked, [this, t, btn]() { selectType(t, btn); });
    }

    QStringList emojis = {"🍒", "⭐️", "💎", "🔔", "7️⃣"};


    symbolWidget = new QWidget();
    QHBoxLayout* symLayout = new QHBoxLayout(symbolWidget);
    for (const QString& s : emojis) {
        QPushButton* btn = new QPushButton(s);
        btn->setStyleSheet(btnStyle);
        btn->setCheckable(true);
        if (s == "🍒") btn->setChecked(true); 
        symbolButtons.push_back(btn);
        symLayout->addWidget(btn);
        connect(btn, &QPushButton::clicked, [this, s, btn]() { selectSymbol(s, btn); });
    }

    // Slots Row (Exact)
    slotsWidget = new QWidget();
    QHBoxLayout* slotsLayout = new QHBoxLayout(slotsWidget);
    for (int i = 0; i < 3; i++) {
        QPushButton* slotBtn = new QPushButton("[ Empty ]");
        slotBtn->setStyleSheet("QPushButton { background-color: #1a1a2e; color: #aaa; font-size: 24px; padding: 15px; border: 2px dashed #555; border-radius: 10px; }");
        exactSlotButtons.push_back(slotBtn);
        slotsLayout->addWidget(slotBtn);
        connect(slotBtn, &QPushButton::clicked, [this, i]() { slotClicked(i); });
    }

    // Pattern Row
    patternWidget = new QWidget();
    QHBoxLayout* patternLayout = new QHBoxLayout(patternWidget);
    QStringList patterns = {"ALL", "PAIR"};
    for (const QString& p : patterns) {
        QPushButton* btn = new QPushButton(p);
        btn->setStyleSheet(btnStyle);
        btn->setCheckable(true);
        if (p == "ALL") btn->setChecked(true);
        patternButtons.push_back(btn);
        patternLayout->addWidget(btn);
        connect(btn, &QPushButton::clicked, [this, p, btn]() { selectPattern(p, btn); });
    }

    amountInput = new QLineEdit();
    amountInput->setPlaceholderText("Enter Prediction Coins (e.g. 50)");
    amountInput->setStyleSheet("padding: 10px; font-size: 16px; border-radius: 5px; color: black; background: white;");

    QPushButton* submit = new QPushButton("Add Prediction");
    submit->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #00ffcc, stop:1 #0099ff); color: black; font-size: 20px; padding: 15px; font-weight: bold; border-radius: 8px;");

    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addWidget(typeLabel);
    layout->addLayout(typeLayout);
    layout->addSpacing(20);

    layout->addWidget(slotsWidget);
    layout->addWidget(symbolWidget);
    layout->addWidget(patternWidget);

    layout->addSpacing(20);
    layout->addWidget(amountInput);
    layout->addWidget(submit);

    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(15);
    layout->setContentsMargins(40, 40, 40, 40);
    this->setStyleSheet("background-color: #0d0e15; color: white;");

    connect(submit, &QPushButton::clicked, [=]() {
        double amt = amountInput->text().toDouble();
        if (amt <= 0) {
            QMessageBox::warning(this, "Error", "Please enter valid coins.");
            return;
        }
        if (amt > maxBalance) {
            QMessageBox::warning(this, "Insufficient Balance", "You cannot place more coins than your balance: " + QString::number(maxBalance));
            return;
        }
        prediction.amount = amt;

        if (selectedType == "EXACT")
        {
            if (selectedExactSymbols.size() < 3) {
                QMessageBox::warning(this, "Error", "Please select 3 symbols for an EXACT match.");
                return;
            }
            prediction.type = EXACT;
            prediction.s1 = emojiToText(selectedExactSymbols[0]).toStdString();
            prediction.s2 = emojiToText(selectedExactSymbols[1]).toStdString();
            prediction.s3 = emojiToText(selectedExactSymbols[2]).toStdString();
        }
        else if (selectedType == "SYMBOL")
        {
            prediction.type = SYMBOL;
            prediction.symbol = emojiToText(selectedSingleSymbol).toStdString();
        }
        else
        {
            prediction.type = PATTERN;
            prediction.pattern = selectedPattern.toStdString();
        }

        accept();
    });

    setLayout(layout);
    setWindowTitle("Prediction Pro");

    this->setFixedSize(700, 650);

    for (auto btn : symbolButtons) {
        btn->setChecked(false);
    }
    
    updateUI();
}

QString PredictionDialog::emojiToText(const QString& emoji) 
{
    if (emoji == "🍒") return "CHERRY";
    if (emoji == "⭐️") return "STAR";
    if (emoji == "💎") return "DIAMOND";
    if (emoji == "🔔") return "BELL";
    if (emoji == "7️⃣") return "7";
    return emoji;
}

void PredictionDialog::selectType(QString type, QPushButton* clickedBtn) 
{
    selectedType = type;
    for (auto btn : typeButtons) {
        btn->setChecked(btn == clickedBtn);
    }
    

    if (type == "EXACT") {
        for (auto btn : symbolButtons) btn->setChecked(false);
    } else if (type == "SYMBOL") {
        for (auto btn : symbolButtons) {
            if (btn->text() == selectedSingleSymbol) btn->setChecked(true);
            else btn->setChecked(false);
        }
    }
    updateUI();
}

void PredictionDialog::selectSymbol(QString symbol, QPushButton* clickedBtn) 
{
    if (selectedType == "EXACT") {
        clickedBtn->setChecked(false);
        if (selectedExactSymbols.size() < 3) {
            selectedExactSymbols.push_back(symbol);
            updateSlotsUI();
        }
    } else {
        selectedSingleSymbol = symbol;
        for (auto btn : symbolButtons) {
            btn->setChecked(btn == clickedBtn);
        }
    }
}

void PredictionDialog::slotClicked(int index) 
{
    if (index >= 0 && index < selectedExactSymbols.size()) {
        selectedExactSymbols.erase(selectedExactSymbols.begin() + index);
        updateSlotsUI();
    }
}

void PredictionDialog::updateSlotsUI() 
{
    for (int i = 0; i < 3; i++) {
        if (i < selectedExactSymbols.size()) {
            exactSlotButtons[i]->setText(selectedExactSymbols[i]);
            exactSlotButtons[i]->setStyleSheet("QPushButton { background-color: #e94560; color: white; font-size: 32px; border: 2px solid #00ffcc; border-radius: 10px; }");
        } else {
            exactSlotButtons[i]->setText("[ Empty ]");
            exactSlotButtons[i]->setStyleSheet("QPushButton { background-color: #1a1a2e; color: #aaa; font-size: 24px; padding: 15px; border: 2px dashed #555; border-radius: 10px; }");
        }
    }
}

void PredictionDialog::selectPattern(QString pattern, QPushButton* clickedBtn) 
{
    selectedPattern = pattern;
    for (auto btn : patternButtons) {
        btn->setChecked(btn == clickedBtn);
    }
}

void PredictionDialog::updateUI()
{
    if (selectedType == "EXACT")
    {
        slotsWidget->show();
        symbolWidget->show();
        patternWidget->hide();
    }
    else if (selectedType == "SYMBOL")
    {
        slotsWidget->hide();
        symbolWidget->show();
        patternWidget->hide();
    }
    else 
    {
        slotsWidget->hide();
        symbolWidget->hide();
        patternWidget->show();
    }
}

Prediction PredictionDialog::getPrediction() const
{
    return prediction;
}

void PredictionDialog::setMaxBalance(double b) {
    maxBalance = b;
    amountInput->clear();
}