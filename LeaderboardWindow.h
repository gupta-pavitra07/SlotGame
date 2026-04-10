#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>

class LeaderboardWindow : public QWidget
{
    Q_OBJECT

public:
    LeaderboardWindow(QWidget *parent = nullptr);

private:
    QTableWidget* table;
    QLineEdit* searchInput;

private slots:
    void loadLeaderboard();
    void searchPlayer();
};

#endif