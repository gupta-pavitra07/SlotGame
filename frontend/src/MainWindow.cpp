#include "MainWindow.h"
#include "ResultDialog.h"
#include "LeaderboardWindow.h"
#include "StrategyDialog.h"
#include "PredictionDialog.h"
#include "ActivePredictionsDialog.h"
#include "ProfileDialog.h"
#include "QuizWidget.h"
#include <QStackedWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QTimer>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QInputDialog>
#include <fstream>

#include "file.h"
#include "probability.h"
#include "strategy.h"

MainWindow::MainWindow(Player playerObj, bool isNewUser, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);

    player = new Player(playerObj);


    QFrame* sidebar = new QFrame();
    sidebar->setFixedWidth(280);
    sidebar->setStyleSheet("QFrame { background-color: #1a1a2e; border-right: 2px solid #e94560; } QPushButton { text-align: left; padding: 15px; font-size: 18px; color: white; background: transparent; border: none; } QPushButton:hover { background-color: #e94560; }");
    QVBoxLayout* sideLayout = new QVBoxLayout(sidebar);
    
    QLabel* logo = new QLabel("🎰 SLOT MACHINE");
    logo->setStyleSheet("font-size: 24px; font-weight: bold; color: #00ffcc; padding: 10px;");
    
    QPushButton* navDashboard = new QPushButton("🎰 Play Slot");
    QPushButton* navPredictions = new QPushButton("🧠 Make Predictions");
    QPushButton* navActive = new QPushButton("📋 Active Predictions");
    QPushButton* navStrategy = new QPushButton("📊 Strategy");
    QPushButton* navLeaderboard = new QPushButton("🏆 Leaderboard");
    QPushButton* navQuizzes = new QPushButton("📝 Tech Quizzes");
    QPushButton* navProfile = new QPushButton("👤 Profile");

    sideLayout->addWidget(logo);
    sideLayout->addSpacing(30);
    sideLayout->addWidget(navDashboard);
    sideLayout->addWidget(navPredictions);
    sideLayout->addWidget(navActive);
    sideLayout->addWidget(navStrategy);
    sideLayout->addWidget(navLeaderboard);
    sideLayout->addWidget(navQuizzes);
    sideLayout->addWidget(navProfile);
    sideLayout->addStretch();

    stackedWidget = new QStackedWidget();


    dashboardWidget = new QWidget();
    QVBoxLayout* dashLayout = new QVBoxLayout(dashboardWidget);
    
    QHBoxLayout* topLayout = new QHBoxLayout();
    nameLabel = new QLabel("👤 Player: " + QString::fromStdString(player->getName()));
    nameLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #00ffcc;");
    
    balanceLabel = new QLabel("💰 Balance: " + QString::number(player->getBalance()) + " Coins");
    balanceLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #00ffcc;");
    balanceLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    topLayout->addWidget(nameLabel);
    topLayout->addWidget(balanceLabel);

    QFrame* reelsFrame = new QFrame();
    reelsFrame->setStyleSheet("QFrame { background-color: #0b0b16; border: 4px solid #e94560; border-radius: 20px; } QLabel { border: none; }");
    reelsFrame->setFixedHeight(300);
    QHBoxLayout* reelLayout = new QHBoxLayout(reelsFrame);

    reel1 = new QLabel("🍒");
    reel2 = new QLabel("⭐");
    reel3 = new QLabel("🔔");
    reel1->setAlignment(Qt::AlignCenter);
    reel2->setAlignment(Qt::AlignCenter);
    reel3->setAlignment(Qt::AlignCenter);
    reel1->setStyleSheet("font-size: 140px;");
    reel2->setStyleSheet("font-size: 140px;");
    reel3->setStyleSheet("font-size: 140px;");
    reelLayout->addWidget(reel1);
    reelLayout->addWidget(reel2);
    reelLayout->addWidget(reel3);

    spinButton = new QPushButton("🎰 SPIN!");
    spinButton->setFixedSize(300, 150);
    spinButton->setStyleSheet(
        "QPushButton { font-size: 40px; font-weight: bold; border-radius: 75px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #00ff87, stop:1 #60efff); color: #0b0b16; border: none; }"
        "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #60efff, stop:1 #00ff87); }"
        "QPushButton:pressed { background: #00b35f; }"
    );
    QHBoxLayout* spinLayout = new QHBoxLayout();
    spinLayout->addStretch();
    spinLayout->addWidget(spinButton);
    spinLayout->addStretch();

    dashLayout->addLayout(topLayout);
    dashLayout->addStretch();
    dashLayout->addWidget(reelsFrame);
    dashLayout->addStretch();
    dashLayout->addLayout(spinLayout);
    dashLayout->setContentsMargins(40, 40, 40, 40);


    profileWidget = new ProfileWidget(player);
    leaderboardWidget = new LeaderboardWindow();
    quizWidget = new QuizWidget(player);
    activePredictionsWidget = new ActivePredictionsDialog(currentPredictions);
    strategyWidget = new StrategyDialog("Enter budget in Dashboard to view strategy.");
    

    predictionWidget = new PredictionDialog(player->getBalance());

    stackedWidget->addWidget(dashboardWidget);        
    stackedWidget->addWidget(predictionWidget);       
    stackedWidget->addWidget(activePredictionsWidget); 
    stackedWidget->addWidget(strategyWidget);         
    stackedWidget->addWidget(leaderboardWidget);      
    stackedWidget->addWidget(quizWidget);             
    stackedWidget->addWidget(profileWidget);          

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);

    connect(spinButton, &QPushButton::clicked, this, &MainWindow::spinSlot);
    

    connect(navDashboard, &QPushButton::clicked, this, [this](){ stackedWidget->setCurrentIndex(0); });
    connect(navPredictions, &QPushButton::clicked, this, [this](){ 
        double totalPlaced = 0;
        for (auto &p : currentPredictions) totalPlaced += p.amount;
        predictionWidget->setMaxBalance(player->getBalance() - totalPlaced);
        stackedWidget->setCurrentIndex(1); 
    });
    connect(navActive, &QPushButton::clicked, this, [this](){ 
        activePredictionsWidget->setPredictions(currentPredictions);
        stackedWidget->setCurrentIndex(2); 
    });
    connect(navStrategy, &QPushButton::clicked, this, [this](){ stackedWidget->setCurrentIndex(3); });
    connect(navLeaderboard, &QPushButton::clicked, this, [this](){
        leaderboardWidget->refresh();
        stackedWidget->setCurrentIndex(4);
    });
    connect(navQuizzes, &QPushButton::clicked, this, [this](){ stackedWidget->setCurrentIndex(5); });
    connect(navProfile, &QPushButton::clicked, this, [this](){
        profileWidget->refresh();
        stackedWidget->setCurrentIndex(6);
    });
    

    connect(predictionWidget, &QDialog::accepted, this, [this](){
        currentPredictions.push_back(predictionWidget->getPrediction());
        balanceLabel->setText("🧠 Prediction Added! (" + QString::number(currentPredictions.size()) + ")");
        stackedWidget->setCurrentIndex(0); // Return to dashboard
    });


    connect(quizWidget, &QuizWidget::coinsRewarded, this, [this](int amt) {
        player->addBalance(amt);
        savePlayer(*player);
        balanceLabel->setText("💰 Balance: " + QString::number(player->getBalance()) + " Coins");
    });
    connect(quizWidget, &QuizWidget::requestSave, this, [this]() {
        savePlayer(*player);
    });

    central->setLayout(mainLayout);
    setCentralWidget(central);
    this->setFixedSize(1200, 768);

    if (isNewUser) {
        QTimer::singleShot(100, this, [this]() {
            QMessageBox::information(this, "Welcome", "Account created successfully with 1000 Coins!");
        });
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
    player->incrementSpins();
    player->addPredictions(currentPredictions.size());

    
    vector<string> symbols = {"🍒", "⭐️", "💎", "🔔", "7️⃣"};


    auto getEmoji = [](const string& sym) {
        if (sym == "CHERRY") return "🍒";
        if (sym == "STAR") return "⭐️";
        if (sym == "DIAMOND") return "💎";
        if (sym == "BELL") return "🔔";
        if (sym == "7") return "7️⃣";
        return sym.c_str();
    };

    QTimer *timer = new QTimer(this);
    int *count = new int(0);   

    connect(timer, &QTimer::timeout, this, [=]() mutable {

        
        reel1->setText(QString::fromStdString(symbols[rand()%5]));
        reel2->setText(QString::fromStdString(symbols[rand()%5]));
        reel3->setText(QString::fromStdString(symbols[rand()%5]));

        (*count)++;

        
        if (*count > 20) {
            timer->stop();

            for (auto r : {reel1, reel2, reel3}) {
                QPropertyAnimation* anim = new QPropertyAnimation(r, "pos");
                anim->setDuration(800);
                anim->setStartValue(QPoint(r->x(), r->y() - 50));
                anim->setEndValue(QPoint(r->x(), r->y()));
                anim->setEasingCurve(QEasingCurve::OutElastic);
                anim->start(QAbstractAnimation::DeleteWhenStopped);
            }

            
            auto result = slot.spin();

            reel1->setText(QString::fromUtf8(getEmoji(result[0])));
            reel2->setText(QString::fromUtf8(getEmoji(result[1])));
            reel3->setText(QString::fromUtf8(getEmoji(result[2])));

            QString res = QString::fromUtf8(getEmoji(result[0])) + " | " + 
                          QString::fromUtf8(getEmoji(result[1])) + " | " + 
                          QString::fromUtf8(getEmoji(result[2]));

            double reward = evaluator.evaluateAll(currentPredictions, result);

            player->addBalance(reward);
            if (reward > 0) {
                player->addWin();
                player->updateWinStats(reward);
            }
            
            std::ofstream histFile("/Users/pavitragupta/DAAPBL/SlotGame/data/history_" + player->getName() + ".txt", std::ios::app);
            for (auto &p : currentPredictions) {
                std::vector<Prediction> singleP = {p};
                double r = evaluator.evaluateAll(singleP, result);
                QString typeStr;
                if (p.type == EXACT) typeStr = "Exact Match";
                else if (p.type == SYMBOL) typeStr = "Symbol Match";
                else if (p.type == PATTERN) typeStr = "Pattern Match (" + QString::fromStdString(p.pattern) + ")";
                
                QString resultStr = (r > 0) ? "WIN" : "LOSS";
                
                histFile << typeStr.toStdString() << "," 
                         << p.amount << "," 
                         << resultStr.toStdString() << "," 
                         << r << "," 
                         << player->getBalance() << std::endl;
            }
            histFile.close();
            
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