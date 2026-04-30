#include "LeaderboardWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "file.h"
#include <algorithm>

LeaderboardWindow::LeaderboardWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* title = new QLabel("🏆 HALL OF FAME");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 36px; font-weight: bold; color: #ffcc00; text-shadow: 2px 2px #000;");

    searchInput = new QLineEdit();
    searchInput->setPlaceholderText("🔍 Search player...");

    QHBoxLayout* sortLayout = new QHBoxLayout();
    sortWealthBtn = new QPushButton("Sort by Balance");
    sortWinsBtn = new QPushButton("Sort by Wins");
    
    QString btnStyle = "QPushButton { background-color: #333; color: white; padding: 8px; border-radius: 5px; } "
                       "QPushButton:hover { background-color: #555; } "
                       "QPushButton:checked { background-color: #e94560; font-weight: bold; }";
    sortWealthBtn->setStyleSheet(btnStyle);
    sortWinsBtn->setStyleSheet(btnStyle);
    sortWealthBtn->setCheckable(true);
    sortWinsBtn->setCheckable(true);
    sortWealthBtn->setChecked(true); 

    sortLayout->addWidget(sortWealthBtn);
    sortLayout->addWidget(sortWinsBtn);
    sortLayout->addStretch();

    connect(sortWealthBtn, &QPushButton::clicked, this, &LeaderboardWindow::sortByWealth);
    connect(sortWinsBtn, &QPushButton::clicked, this, &LeaderboardWindow::sortByWins);

    table = new QTableWidget();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Username", "Balance (Coins)", "Wins"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    

    table->setStyleSheet(
        "QTableWidget { background-color: transparent; color: white; gridline-color: transparent; border: none; font-size: 18px; }"
        "QHeaderView::section { background-color: transparent; color: #00ffcc; font-size: 20px; font-weight: bold; border: none; padding-bottom: 10px; border-bottom: 2px solid #e94560; }"
        "QTableWidget::item { padding: 15px; border-bottom: 1px solid rgba(233, 69, 96, 0.3); }"
    );
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setShowGrid(false);

    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addWidget(searchInput);
    layout->addLayout(sortLayout);
    layout->addWidget(table);

    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(15);
    layout->setContentsMargins(50, 50, 50, 50);

    setLayout(layout);
    setWindowTitle("Leaderboard Pro");
    this->setFixedSize(900, 600);
    this->setStyleSheet("background-color: #0b0b16;");
    connect(searchInput, &QLineEdit::textChanged,
            this, &LeaderboardWindow::searchPlayer);

    loadLeaderboard();
}

void LeaderboardWindow::sortByWealth()
{
    sortWealthBtn->setChecked(true);
    sortWinsBtn->setChecked(false);
    currentSortMode = WEALTH;
    loadLeaderboard();
}

void LeaderboardWindow::sortByWins()
{
    sortWealthBtn->setChecked(false);
    sortWinsBtn->setChecked(true);
    currentSortMode = WINS;
    loadLeaderboard();
}


void merge(std::vector<Player>& arr, int l, int m, int r, int sortMode) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Player> L(arr.begin() + l, arr.begin() + m + 1);
    vector<Player> R(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        bool condition = false;
        if (sortMode == 0) 
            condition = L[i].getBalance() > R[j].getBalance();
        else               
            condition = L[i].getWins() > R[j].getWins();

        if (condition) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Player>& arr, int l, int r, int sortMode) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, sortMode);
    mergeSort(arr, m + 1, r, sortMode);
    merge(arr, l, m, r, sortMode);
}

void LeaderboardWindow::loadLeaderboard()
{
    std::vector<Player> players = loadPlayers();

    if (!players.empty()) {
        mergeSort(players, 0, players.size() - 1, currentSortMode);
    }

    table->setRowCount(players.size());

    for (int i = 0; i < players.size(); i++)
    {
        QString medal = "";
        if (i == 0) medal = "🥇 ";
        else if (i == 1) medal = "🥈 ";
        else if (i == 2) medal = "🥉 ";

        QTableWidgetItem* nameItem = new QTableWidgetItem(medal + QString::fromStdString(players[i].getName()));
        nameItem->setTextAlignment(Qt::AlignCenter);
        
        QTableWidgetItem* balItem = new QTableWidgetItem(QString::number(players[i].getBalance()));
        balItem->setTextAlignment(Qt::AlignCenter);
        
        QTableWidgetItem* winsItem = new QTableWidgetItem(QString::number(players[i].getWins()));
        winsItem->setTextAlignment(Qt::AlignCenter);

        if (i == 0) { 
            nameItem->setForeground(QColor("#ffcc00"));
            balItem->setForeground(QColor("#ffcc00"));
            winsItem->setForeground(QColor("#ffcc00"));
            QFont font("Arial", 14, QFont::Bold);
            nameItem->setFont(font);
            balItem->setFont(font);
            winsItem->setFont(font);
        } else if (i == 1) { 
            nameItem->setForeground(QColor("#c0c0c0"));
            balItem->setForeground(QColor("#c0c0c0"));
            winsItem->setForeground(QColor("#c0c0c0"));
            QFont font("Arial", 13, QFont::Bold);
            nameItem->setFont(font);
            balItem->setFont(font);
            winsItem->setFont(font);
        } else if (i == 2) { 
            nameItem->setForeground(QColor("#cd7f32"));
            balItem->setForeground(QColor("#cd7f32"));
            winsItem->setForeground(QColor("#cd7f32"));
            QFont font("Arial", 12, QFont::Bold);
            nameItem->setFont(font);
            balItem->setFont(font);
            winsItem->setFont(font);
        }

        table->setItem(i, 0, nameItem);
        table->setItem(i, 1, balItem);
        table->setItem(i, 2, winsItem);
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

void LeaderboardWindow::refresh() {
    loadLeaderboard();
}