#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include "include/player.h"
#include "include/slot.h"
#include "include/predictionevaluator.h"
#include <QStackedWidget>

class PredictionDialog;
class ActivePredictionsDialog;
class LeaderboardWindow;
class StrategyDialog;
class ProfileWidget;
class QuizWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Player playerObj, bool isNewUser = false, QWidget *parent = nullptr);

private slots:
    void spinSlot();

private:
    Player* player;
    SlotMachine slot;
    PredictionEvaluator evaluator;

    QLabel* balanceLabel;
    QLabel* nameLabel;

    QLabel* reel1;
    QLabel* reel2;
    QLabel* reel3;

    QPushButton* spinButton;
    QPushButton* leaderboardButton;
    QPushButton* strategyButton;
    QPushButton* predictionButton;
    QPushButton* profileButton;
    QPushButton* quizButton;

    std::vector<Prediction> currentPredictions;

    QStackedWidget* stackedWidget;
    QWidget* dashboardWidget;
    PredictionDialog* predictionWidget;
    LeaderboardWindow* leaderboardWidget;
    ActivePredictionsDialog* activePredictionsWidget;
    StrategyDialog* strategyWidget;
    ProfileWidget* profileWidget;
    QuizWidget* quizWidget;
};

#endif