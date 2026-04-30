#ifndef ACTIVEPREDICTIONSDIALOG_H
#define ACTIVEPREDICTIONSDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QLabel>
#include <vector>
#include "prediction.h"

class ActivePredictionsDialog : public QDialog
{
    Q_OBJECT

public:
    ActivePredictionsDialog(const vector<Prediction>& predictions, QWidget *parent = nullptr);
    void setPredictions(const vector<Prediction>& predictions);

private:
    QTableWidget* table;
    QLabel* totalLabel;
};

#endif
