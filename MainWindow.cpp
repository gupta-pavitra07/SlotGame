#include "MainWindow.h"
#include "ResultDialog.h"
#include "LeaderboardWindow.h"
#include "StrategyDialog.h"
#include "PredictionDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

#include "include/file.h"
#include "include/probability.h"

MainWindow::MainWindow(QString name, double balance, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    player = new Player(name.toStdString(), balance);

    balanceLabel = new QLabel("Balance: ₹" + QString::number(balance));
    balanceLabel->setAlignment(Qt::AlignCenter);

    reel1 = new QLabel("🍒");
    reel2 = new QLabel("⭐");
    reel3 = new QLabel("🔔");

    reel1->setAlignment(Qt::AlignCenter);
    reel2->setAlignment(Qt::AlignCenter);
    reel3->setAlignment(Qt::AlignCenter);

    reel1->setStyleSheet("font-size: 80px;");
    reel2->setStyleSheet("font-size: 80px;");
    reel3->setStyleSheet("font-size: 80px;");

    QHBoxLayout* reelLayout = new QHBoxLayout();
    reelLayout->addWidget(reel1);
    reelLayout->addWidget(reel2);
    reelLayout->addWidget(reel3);

    betInput = new QLineEdit();
    betInput->setPlaceholderText("Enter amount");

    strategyButton = new QPushButton("📊 Get Strategy");
    predictionButton = new QPushButton("🧠 Make Predictions");
    spinButton = new QPushButton("🎰 Spin");
    leaderboardButton = new QPushButton("🏆 Leaderboard");

    layout->addWidget(balanceLabel);
    layout->addLayout(reelLayout);
    layout->addWidget(betInput);
    layout->addWidget(strategyButton);
    layout->addWidget(predictionButton);
    layout->addWidget(spinButton);
    layout->addWidget(leaderboardButton);

    connect(spinButton, &QPushButton::clicked, this, &MainWindow::spinSlot);
    connect(leaderboardButton, &QPushButton::clicked, this, &MainWindow::openLeaderboard);
    connect(strategyButton, &QPushButton::clicked, this, &MainWindow::getStrategy);
    connect(predictionButton, &QPushButton::clicked, this, &MainWindow::makePrediction);

    central->setLayout(layout);
    setCentralWidget(central);
    this->setFixedSize(800, 500);
}

void MainWindow::getStrategy()
{
    Probability prob;
    SlotMachine slot;

    auto probs = slot.getSymbolProbabilities();

    double bestSymbol = 0;
    for (auto &p : probs)
        bestSymbol = std::max(bestSymbol, p.second);

    double evSymbol = prob.symbolMatchProb(bestSymbol) * 1.5;

    QString result = "Best Strategy: Symbol Match";

    StrategyDialog* dialog = new StrategyDialog(result, this);
    dialog->exec();
}

void MainWindow::makePrediction()
{
    PredictionDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        currentPredictions.clear();
        currentPredictions.push_back(dialog.getPrediction());

        balanceLabel->setText("🧠 Prediction Added!");
    }
}

void MainWindow::spinSlot()
{
    if (currentPredictions.empty())
        return;

    double totalAmount = 0;
    for (auto &p : currentPredictions)
        totalAmount += p.amount;

    if (totalAmount > player->getBalance())
        return;

    player->deductBalance(totalAmount);

    
    vector<string> symbols = {"🍒", "⭐️", "💎", "🔔", "7️⃣"};

    QTimer *timer = new QTimer(this);
    int *count = new int(0);   

    connect(timer, &QTimer::timeout, this, [=]() mutable {

        
        reel1->setText(QString::fromStdString(symbols[rand()%5]));
        reel2->setText(QString::fromStdString(symbols[rand()%5]));
        reel3->setText(QString::fromStdString(symbols[rand()%5]));

        (*count)++;

        
        if (*count > 20) {
            timer->stop();

            
            auto result = slot.spin();

            reel1->setText(QString::fromStdString(result[0]));
            reel2->setText(QString::fromStdString(result[1]));
            reel3->setText(QString::fromStdString(result[2]));

            QString res = QString::fromStdString(
                result[0] + " | " + result[1] + " | " + result[2]);

            double reward = evaluator.evaluateAll(currentPredictions, result);

            player->addBalance(reward);
            currentPredictions.clear();

            savePlayer(*player);

            balanceLabel->setText("Balance: ₹" +
                QString::number(player->getBalance()));

            ResultDialog* dialog = new ResultDialog(
                res,
                reward,
                player->getBalance(),
                this
            );

            dialog->exec();

            
            delete count;
            timer->deleteLater();
        }
    });

    timer->start(80); 
}
void MainWindow::openLeaderboard()
{
    LeaderboardWindow* lb = new LeaderboardWindow();
    lb->show();
}