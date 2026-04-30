#ifndef PREDICTIONDIALOG_H
#define PREDICTIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <vector>
#include "prediction.h"

class PredictionDialog : public QDialog
{
    Q_OBJECT

public:
    PredictionDialog(double currentBalance, QWidget *parent = nullptr);
    Prediction getPrediction() const;
    void setMaxBalance(double b);

private slots:
    void updateUI();
    void selectType(QString type, QPushButton* clickedBtn);
    void selectSymbol(QString symbol, QPushButton* clickedBtn);
    void selectPattern(QString pattern, QPushButton* clickedBtn);
    void slotClicked(int index);

private:
    QString selectedType = "EXACT";
    QString selectedSingleSymbol = "🍒";
    QString selectedPattern = "ALL";
    std::vector<QString> selectedExactSymbols; 

    std::vector<QPushButton*> typeButtons;
    std::vector<QPushButton*> symbolButtons;
    std::vector<QPushButton*> patternButtons;
    
    std::vector<QPushButton*> exactSlotButtons;

    QWidget* symbolWidget;
    QWidget* slotsWidget;
    QWidget* patternWidget;

    QLineEdit* amountInput;
    double maxBalance;

    Prediction prediction;
    
    void updateSlotsUI();
    QString emojiToText(const QString& emoji);
};

#endif