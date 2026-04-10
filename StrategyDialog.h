#ifndef STRATEGYDIALOG_H
#define STRATEGYDIALOG_H

#include <QDialog>

class StrategyDialog : public QDialog
{
    Q_OBJECT

public:
    StrategyDialog(QString strategyText, QWidget *parent = nullptr);
};

#endif