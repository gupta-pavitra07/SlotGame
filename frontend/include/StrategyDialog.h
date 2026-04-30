#ifndef STRATEGYDIALOG_H
#define STRATEGYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class StrategyDialog : public QDialog
{
    Q_OBJECT

public:
    StrategyDialog(QString strategyText, QWidget *parent = nullptr);
    void setStrategyText(const QString& text);

private slots:
    void calculateStrategy();

private:
    QLineEdit* budgetInput;
    QPushButton* calcButton;
    QLabel* contentLabel;
};

#endif