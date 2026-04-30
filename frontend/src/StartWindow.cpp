#include "StartWindow.h"
#include "MainWindow.h"
#include "file.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QMessageBox>
#include <QRegularExpression>

StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFrame* centerBox = new QFrame();
    centerBox->setStyleSheet("QFrame { background-color: rgba(22, 24, 36, 0.9); border-radius: 20px; border: 2px solid #ff0055; }");
    centerBox->setFixedSize(500, 450);

    QVBoxLayout* boxLayout = new QVBoxLayout(centerBox);
    boxLayout->setContentsMargins(40, 40, 40, 40);

    QLabel* title = new QLabel("🎰 SLOT MACHINE 🎰");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 36px; font-weight: bold; color: #00f0ff; border: none; background: transparent;");

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Username...");
    nameInput->setMinimumHeight(55);

    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Password...");
    passwordInput->setMinimumHeight(55);
    passwordInput->setEchoMode(QLineEdit::Password);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    loginButton = new QPushButton("Login");
    loginButton->setMinimumHeight(55);
    
    registerButton = new QPushButton("Create Account");
    registerButton->setMinimumHeight(55);

    btnLayout->addWidget(loginButton);
    btnLayout->addWidget(registerButton);

    boxLayout->addStretch();
    boxLayout->addWidget(title);
    boxLayout->addSpacing(40);
    boxLayout->addWidget(nameInput);
    boxLayout->addSpacing(15);
    boxLayout->addWidget(passwordInput);
    boxLayout->addSpacing(40);
    boxLayout->addLayout(btnLayout);
    boxLayout->addStretch();

    mainLayout->addWidget(centerBox, 0, Qt::AlignCenter);

    connect(loginButton, &QPushButton::clicked, this, &StartWindow::login);
    connect(registerButton, &QPushButton::clicked, this, &StartWindow::registerUser);

    setLayout(mainLayout);
    setWindowTitle("Slot Game Pro - Login");

    this->setFixedSize(1024, 768);
}

bool StartWindow::isValidPassword(const QString& pwd)
{
    if (pwd.length() < 6) return false;
    QRegularExpression upper("[A-Z]");
    QRegularExpression lower("[a-z]");
    QRegularExpression special("[!@#$%^&*(),.?\":{}|<>]");
    return upper.match(pwd).hasMatch() && lower.match(pwd).hasMatch() && special.match(pwd).hasMatch();
}

void StartWindow::login()
{
    QString name = nameInput->text();
    QString password = passwordInput->text();

    if (name.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter username and password.");
        return;
    }

    std::vector<Player> players = loadPlayers();
    for (auto& p : players) {
        if (p.getName() == name.toStdString()) {
            if (p.getPassword() == password.toStdString()) {
                bool isNewUser = (name == registeredUser);
                MainWindow* game = new MainWindow(
                    p, 
                    isNewUser
                );
                game->show();
                this->close();
                return;
            } else {
                QMessageBox::warning(this, "Error", "Incorrect password!");
                return;
            }
        }
    }
    
    QMessageBox::warning(this, "Error", "User not found. Please create an account.");
}

void StartWindow::registerUser()
{
    QString name = nameInput->text();
    QString password = passwordInput->text();

    if (name.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter username and password.");
        return;
    }

    if (!isValidPassword(password)) {
        QMessageBox::warning(this, "Error", "Password must be at least 6 characters, and contain an uppercase, lowercase, and special character.");
        return;
    }

    std::vector<Player> players = loadPlayers();
    for (auto& p : players) {
        if (p.getName() == name.toStdString()) {
            QMessageBox::warning(this, "Error", "Username already exists.");
            return;
        }
    }

    Player newPlayer(name.toStdString(), 1000.0, password.toStdString());
    savePlayer(newPlayer);
    
    registeredUser = name;
    
    QMessageBox::information(this, "Success", "Account created successfully! Please login with your new credentials.");
    
    registerButton->hide(); 
    

    nameInput->clear();
    passwordInput->clear();
}