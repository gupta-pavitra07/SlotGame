#include "ActivePredictionsDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>

ActivePredictionsDialog::ActivePredictionsDialog(const std::vector<Prediction>& predictions, QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("📋 Your Active Predictions");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: #00ffcc;");

    table = new QTableWidget();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Type", "Details", "Coins"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->setStyleSheet(
        "QTableWidget { background-color: transparent; color: white; border: none; font-size: 16px; }"
        "QHeaderView::section { background-color: transparent; color: #e94560; font-size: 18px; font-weight: bold; border: none; border-bottom: 2px solid #e94560; }"
        "QTableWidget::item { padding: 10px; border-bottom: 1px solid rgba(233, 69, 96, 0.3); }"
    );
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setShowGrid(false);

    totalLabel = new QLabel("Total Coins Placed: 0");
    totalLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #ffcc00;");
    totalLabel->setAlignment(Qt::AlignRight);

    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addWidget(table);
    layout->addWidget(totalLabel);

    this->setStyleSheet("background-color: #0b0b16; color: white;");

    setPredictions(predictions);
}

void ActivePredictionsDialog::setPredictions(const std::vector<Prediction>& predictions) {
    double totalCoins = 0;
    table->setRowCount(predictions.size());
    for (int i = 0; i < predictions.size(); i++)
    {
        const auto& p = predictions[i];
        QString typeStr, detailsStr;
        if (p.type == EXACT) {
            typeStr = "Exact Match";
            detailsStr = QString::fromStdString(p.s1 + " | " + p.s2 + " | " + p.s3);
        } else if (p.type == SYMBOL) {
            typeStr = "Symbol Match";
            detailsStr = QString::fromStdString(p.symbol);
        } else {
            typeStr = "Pattern Match";
            detailsStr = QString::fromStdString(p.pattern);
        }

        QTableWidgetItem* typeItem = new QTableWidgetItem(typeStr);
        QTableWidgetItem* detailsItem = new QTableWidgetItem(detailsStr);
        QTableWidgetItem* coinsItem = new QTableWidgetItem(QString::number(p.amount));
        
        typeItem->setTextAlignment(Qt::AlignCenter);
        detailsItem->setTextAlignment(Qt::AlignCenter);
        coinsItem->setTextAlignment(Qt::AlignCenter);

        table->setItem(i, 0, typeItem);
        table->setItem(i, 1, detailsItem);
        table->setItem(i, 2, coinsItem);
        
        totalCoins += p.amount;
    }

    totalLabel->setText("Total Coins Placed: " + QString::number(totalCoins));
}
