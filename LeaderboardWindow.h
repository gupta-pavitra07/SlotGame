#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>

class LeaderboardWindow : public QWidget
{
    Q_OBJECT

public:
    LeaderboardWindow(QWidget *parent = nullptr);
    void refresh();

private:
    QTableWidget* table;
    QLineEdit* searchInput;
    QPushButton* sortWealthBtn;
    QPushButton* sortWinsBtn;
    
    enum SortMode { WEALTH, WINS };
    SortMode currentSortMode = WEALTH;

private slots:
    void loadLeaderboard();
    void searchPlayer();
    void sortByWealth();
    void sortByWins();
};

#endif