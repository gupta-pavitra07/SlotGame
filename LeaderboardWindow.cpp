#include "LeaderboardWindow.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>

#include "include/file.h"
#include <algorithm>

LeaderboardWindow::LeaderboardWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();

    
    QLabel* title = new QLabel("🏆 Leaderboard");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 26px; font-weight: bold;");

    
    searchInput = new QLineEdit();
    searchInput->setPlaceholderText("Search player...");


    table = new QTableWidget();
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Name", "Balance"});
    table->horizontalHeader()->setStretchLastSection(true);

    
    layout->addWidget(title);
    layout->addWidget(searchInput);
    layout->addWidget(table);

    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 30, 30, 30);

    setLayout(layout);
    setWindowTitle("Leaderboard");
    this->setFixedSize(800, 500);
    connect(searchInput, &QLineEdit::textChanged,
            this, &LeaderboardWindow::searchPlayer);

    
    loadLeaderboard();
}
void LeaderboardWindow::loadLeaderboard()
{
    std::vector<Player> players = loadPlayers();

    std::sort(players.begin(), players.end(),
        [](Player a, Player b)
        {
            return a.getBalance() > b.getBalance();
        });

    table->setRowCount(players.size());

    for (int i = 0; i < players.size(); i++)
    {
        table->setItem(i, 0,
            new QTableWidgetItem(QString::fromStdString(players[i].getName())));

        table->setItem(i, 1,
            new QTableWidgetItem(QString::number(players[i].getBalance())));
    }
}

void LeaderboardWindow::searchPlayer()
{
    QString text = searchInput->text().toLower();

    for (int i = 0; i < table->rowCount(); i++)
    {
        QString name = table->item(i, 0)->text().toLower();

        bool match = name.contains(text);
        table->setRowHidden(i, !match);
    }
}