#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QLabel>

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    ResultDialog(QString result,
                 double reward,
                 double balance,
                 QWidget *parent = nullptr);
};

#endif