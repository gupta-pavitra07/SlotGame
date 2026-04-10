#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include "include/player.h"
#include "include/slot.h"
#include "include/predictionevaluator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString name, double balance, QWidget *parent = nullptr);

private slots:
    void spinSlot();
    void openLeaderboard();
    void getStrategy();
    void makePrediction();

private:
    Player* player;
    SlotMachine slot;
    PredictionEvaluator evaluator;

    QLabel* balanceLabel;

    QLabel* reel1;
    QLabel* reel2;
    QLabel* reel3;

    QLineEdit* betInput;

    QPushButton* spinButton;
    QPushButton* leaderboardButton;
    QPushButton* strategyButton;
    QPushButton* predictionButton;

    std::vector<Prediction> currentPredictions;
};

#endif