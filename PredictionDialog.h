#ifndef PREDICTIONDIALOG_H
#define PREDICTIONDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include "include/prediction.h"

class PredictionDialog : public QDialog
{
    Q_OBJECT

public:
    PredictionDialog(QWidget *parent = nullptr);
    Prediction getPrediction();

private slots:
    void updateUI();

private:
    QComboBox* typeBox;
    QComboBox* symbolBox;

    QLineEdit* input2;
    QLineEdit* input3;

    QLineEdit* amountInput;

    Prediction prediction;
};

#endif