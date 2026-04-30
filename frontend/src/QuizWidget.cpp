#include "QuizWidget.h"
#include <QDateTime>
#include <QTimer>
#include <algorithm>
#include <random>
#include <chrono>

QuizWidget::QuizWidget(Player* p, QWidget* parent) : QWidget(parent), player(p) 
{
    loadQuestions();
    
    mainLayout = new QVBoxLayout(this);
    
    titleLabel = new QLabel("🧠 DAA Tech Quiz 🧠");
    titleLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #00ffcc;");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    statusLabel = new QLabel("");
    statusLabel->setStyleSheet("font-size: 18px; color: #aaa;");
    statusLabel->setAlignment(Qt::AlignCenter);

    questionLabel = new QLabel("");
    questionLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    questionLabel->setAlignment(Qt::AlignCenter);
    questionLabel->setWordWrap(true);

    optionsLayout = new QVBoxLayout();
    for (int i = 0; i < 4; i++) {
        QPushButton* btn = new QPushButton("");
        btn->setStyleSheet(
            "QPushButton { background-color: #2a2a40; color: white; padding: 15px; border-radius: 8px; font-size: 20px; border: 2px solid #333; }"
            "QPushButton:hover { background-color: #e94560; border: 2px solid #00ffcc; }"
        );
        optionButtons.push_back(btn);
        optionsLayout->addWidget(btn);
        connect(btn, &QPushButton::clicked, [this, i]() { handleAnswer(i); });
    }

    startButton = new QPushButton("Start Quiz (10 Questions)");
    startButton->setStyleSheet(
        "QPushButton { background-color: #00ffcc; color: black; font-size: 24px; padding: 15px; font-weight: bold; border-radius: 10px; }"
        "QPushButton:hover { background-color: #00ccaa; }"
    );
    connect(startButton, &QPushButton::clicked, this, &QuizWidget::startQuiz);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(statusLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(questionLabel);
    mainLayout->addLayout(optionsLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(startButton);
    
    this->setStyleSheet("background-color: #0b0b16;");
    
    updateUI();
}

void QuizWidget::updateUI() {
    QString today = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    if (player->getLastQuizDate() == today.toStdString() && player->getQuizzesAttempted() >= 5) {
        startButton->setEnabled(false);
        startButton->setText("Daily Limit Reached (5/5)");
        statusLabel->setText("You have completed all 5 quizzes for today! Come back tomorrow.");
    } else {
        int attempts = (player->getLastQuizDate() == today.toStdString()) ? player->getQuizzesAttempted() : 0;
        statusLabel->setText("Quizzes Attempted Today: " + QString::number(attempts) + "/5\nEarn 10 coins per correct answer!");
        startButton->setEnabled(true);
        startButton->setText("Start Quiz (10 Questions)");
    }
    
    questionLabel->hide();
    for (auto btn : optionButtons) btn->hide();
    startButton->show();
}

void QuizWidget::startQuiz() {
    QString today = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    if (player->getLastQuizDate() == today.toStdString() && player->getQuizzesAttempted() >= 5) return;
    
    player->attemptQuiz(today.toStdString());
    emit requestSave();
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(allQuestions.begin(), allQuestions.end(), std::default_random_engine(seed));
    
    currentQuiz.clear();
    for (int i = 0; i < 10; i++) currentQuiz.push_back(allQuestions[i]);
    
    currentQuestionIndex = 0;
    score = 0;
    
    startButton->hide();
    questionLabel->show();
    for (auto btn : optionButtons) btn->show();
    
    showNextQuestion();
}

void QuizWidget::showNextQuestion() {
    statusLabel->setText("Question " + QString::number(currentQuestionIndex + 1) + " of 10 | Score: " + QString::number(score));
    
    Question q = currentQuiz[currentQuestionIndex];
    questionLabel->setText(QString::fromStdString(q.text));
    
    for (int i = 0; i < 4; i++) {
        optionButtons[i]->setText(QString::fromStdString(q.options[i]));
        optionButtons[i]->setEnabled(true);
        optionButtons[i]->setStyleSheet(
            "QPushButton { background-color: #2a2a40; color: white; padding: 15px; border-radius: 8px; font-size: 20px; border: 2px solid #333; }"
            "QPushButton:hover { background-color: #e94560; border: 2px solid #00ffcc; }"
        );
    }
}

void QuizWidget::handleAnswer(int index) {
    for (auto btn : optionButtons) btn->setEnabled(false);
    
    int correct = currentQuiz[currentQuestionIndex].correctIndex;
    
    if (index == correct) {
        optionButtons[index]->setStyleSheet("QPushButton { background-color: #00ff99; color: black; font-weight: bold; font-size: 20px; padding: 15px; border-radius: 8px;}");
        score++;
    } else {
        optionButtons[index]->setStyleSheet("QPushButton { background-color: #ff3333; color: white; font-weight: bold; font-size: 20px; padding: 15px; border-radius: 8px;}");
        optionButtons[correct]->setStyleSheet("QPushButton { background-color: #00ff99; color: black; font-weight: bold; font-size: 20px; padding: 15px; border-radius: 8px;}");
    }
    
    QTimer::singleShot(1500, this, [this]() {
        currentQuestionIndex++;
        if (currentQuestionIndex < 10) {
            showNextQuestion();
        } else {
            endQuiz();
        }
    });
}

void QuizWidget::endQuiz() {
    int coinsEarned = score * 10;
    statusLabel->setText("Quiz Finished! You scored " + QString::number(score) + "/10.");
    questionLabel->setText("You earned " + QString::number(coinsEarned) + " Coins!");
    
    for (auto btn : optionButtons) btn->hide();
    
    emit coinsRewarded(coinsEarned);
    
    QTimer::singleShot(3000, this, [this]() {
        updateUI();
    });
}

void QuizWidget::loadQuestions() {
    allQuestions = get50Questions();
}
