#include "ProfileDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QString>
#include <QHeaderView>
#include <QPushButton>
#include <fstream>
#include <sstream>

HistoryDialog::HistoryDialog(Player* p, QWidget *parent) : QDialog(parent) 
{
    setWindowTitle("Game History");
    setFixedSize(800, 600);
    setStyleSheet("background-color: #0b0b16; color: white;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("📜 Game History");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #ffcc00;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QTableWidget* table = new QTableWidget();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Prediction Type", "Amount", "Win/Loss", "Win/Loss Amount", "Final Balance"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    std::ifstream file("/Users/pavitragupta/DAAPBL/SlotGame/data/history_" + p->getName() + ".txt");
    std::string line;
    int row = 0;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type, amt, wl, wlAmt, bal;
        std::getline(ss, type, ',');
        std::getline(ss, amt, ',');
        std::getline(ss, wl, ',');
        std::getline(ss, wlAmt, ',');
        std::getline(ss, bal, ',');

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(type)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(amt)));
        
        QTableWidgetItem* wlItem = new QTableWidgetItem(QString::fromStdString(wl));
        if (wl == "WIN") 
        {
            wlItem->setForeground(QBrush(Qt::green));
            table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(wlAmt)));
        }
        else
        { 
            wlItem->setForeground(QBrush(Qt::red));
            table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(amt)));
            
        }
        table->setItem(row, 2, wlItem);
        
       
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(bal)));
        row++;
    }
    file.close();

    layout->addWidget(table);
    
    QPushButton* closeBtn = new QPushButton("Close");
    closeBtn->setFixedSize(150, 40);
    closeBtn->setStyleSheet("background-color: #e94560; color: white; font-weight: bold; border-radius: 5px;");
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(closeBtn);
    btnLayout->addStretch();
    
    layout->addLayout(btnLayout);
}

ProfileWidget::ProfileWidget(Player* p, QWidget *parent)
    : QWidget(parent), player(p)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* title = new QLabel("👤 PLAYER PROFILE");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 32px; font-weight: bold; color: #ffcc00;");

    QFrame* statsFrame = new QFrame();
    statsFrame->setStyleSheet("QFrame { background-color: #1a1a2e; border: 2px solid #e94560; border-radius: 15px; padding: 20px; }");
    statsLayout = new QVBoxLayout(statsFrame);

    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addWidget(statsFrame);

    QPushButton* historyBtn = new QPushButton("📜 View History");
    historyBtn->setFixedSize(200, 40);
    historyBtn->setStyleSheet("background-color: #00f0ff; color: #0b0b16; font-weight: bold; font-size: 16px; border-radius: 5px;");
    connect(historyBtn, &QPushButton::clicked, this, [this](){
        HistoryDialog* dlg = new HistoryDialog(player, this);
        dlg->exec();
    });
    layout->addWidget(historyBtn, 0, Qt::AlignCenter);

    layout->addStretch();

    this->setStyleSheet("background-color: #0b0b16; color: white;");
    refresh();
}

void ProfileWidget::refresh() {
    QLayoutItem *child;
    while ((child = statsLayout->takeAt(0)) != nullptr) {
        if (child->layout()) {
            QLayout* rowLayout = child->layout();
            QLayoutItem* item;
            while ((item = rowLayout->takeAt(0)) != nullptr) {
                if (item->widget()) {
                    delete item->widget();
                }
                delete item;
            }
        }
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }

    auto addStat = [this](QString labelText, QString valueText) {
        QHBoxLayout* row = new QHBoxLayout();
        QLabel* label = new QLabel(labelText);
        label->setStyleSheet("font-size: 20px; color: #aaa; border: none;");
        QLabel* value = new QLabel(valueText);
        value->setStyleSheet("font-size: 22px; font-weight: bold; color: white; border: none;");
        value->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        row->addWidget(label);
        row->addWidget(value);
        statsLayout->addLayout(row);
    };

    int spins = player->getTotalSpins();
    int wins = player->getWins();
    int losses = spins - wins;
    if (losses < 0) losses = 0;
    double winRate = (spins > 0) ? (double(wins) / spins) * 100.0 : 0.0;

    addStat("Name:", QString::fromStdString(player->getName()));
    addStat("Balance:", QString::number(player->getBalance()) + " Coins");
    addStat("Total Spins:", QString::number(spins));
    addStat("Wins:", QString::number(wins));
    addStat("Losses:", QString::number(losses));
    addStat("Total Predictions:", QString::number(player->getTotalPredictions()));
    addStat("Win Percentage:", QString::number(winRate, 'f', 1) + "%");
    addStat("Largest Win:", QString::number(player->getLargestWin()) + " Coins");
    addStat("Total Coins Won:", QString::number(player->getTotalCoinsWon()) + " Coins");
}
