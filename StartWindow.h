#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);

private slots:
    void login();
    void registerUser();

private:
    QLineEdit* nameInput;
    QLineEdit* passwordInput;
    QPushButton* loginButton;
    QPushButton* registerButton;

    QString registeredUser = "";

    bool isValidPassword(const QString& pwd);
};

#endif