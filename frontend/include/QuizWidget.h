#ifndef QUIZWIDGET_H
#define QUIZWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>
#include "player.h"
#include "questions.h"

class QuizWidget : public QWidget {
    Q_OBJECT

public:
    QuizWidget(Player* player, QWidget* parent = nullptr);

signals:
    void coinsRewarded(int amount);
    void requestSave();

private slots:
    void startQuiz();

private:
    Player* player;
    std::vector<Question> allQuestions;
    std::vector<Question> currentQuiz;
    int currentQuestionIndex;
    int score;

    QLabel* titleLabel;
    QLabel* questionLabel;
    QLabel* statusLabel;
    std::vector<QPushButton*> optionButtons;
    QPushButton* startButton;
    QVBoxLayout* mainLayout;
    QVBoxLayout* optionsLayout;

    void loadQuestions();
    void showNextQuestion();
    void handleAnswer(int index);
    void endQuiz();
    void updateUI();
};

#endif
