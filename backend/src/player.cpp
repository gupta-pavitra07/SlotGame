#include "../include/player.h"
#include <iostream>

Player::Player(std::string name, double balance, std::string password, int wins, int totalSpins, int totalPredictions, double totalCoinsWon, double largestWin, int quizzesAttempted, string lastQuizDate)
    : name(std::move(name)), balance(balance), password(std::move(password)), wins(wins), 
      totalSpins(totalSpins), totalPredictions(totalPredictions), totalCoinsWon(totalCoinsWon), largestWin(largestWin),
      quizzesAttempted(quizzesAttempted), lastQuizDate(std::move(lastQuizDate)) {}

std::string Player::getName() 
{
    return name;
}

std::string Player::getPassword() 
{
    return password;
}

double Player::getBalance() const 
{
    return balance;
}

int Player::getWins() const 
{
    return wins;
}

int Player::getTotalSpins() const { return totalSpins; }
int Player::getTotalPredictions() const { return totalPredictions; }
double Player::getTotalCoinsWon() const { return totalCoinsWon; }
double Player::getLargestWin() const { return largestWin; }
int Player::getQuizzesAttempted() const { return quizzesAttempted; }
std::string Player::getLastQuizDate() const { return lastQuizDate; }

void Player::addBalance(double amount) 
{
    balance += amount;
}

void Player::deductBalance(double amount) 
{
    if (amount <= balance) balance -= amount;
}

void Player::addWin() 
{
    wins++;
}

void Player::incrementSpins() 
{
    totalSpins++;
}

void Player::addPredictions(int count) 
{
    totalPredictions += count;
}

void Player::updateWinStats(double coinsWon) 
{
    totalCoinsWon += coinsWon;
    if (coinsWon > largestWin) largestWin = coinsWon;
}

void Player::attemptQuiz(std::string currentDate) 
{
    if (lastQuizDate != currentDate) {
        lastQuizDate = currentDate;
        quizzesAttempted = 1;
    } else {
        quizzesAttempted++;
    }
}

void Player::addHistory(std::string record) 
{
    history.push_back(std::move(record));
}

void Player::showHistory() 
{
    for (const auto& rec : history) {
        std::cout << rec << std::endl;
    }
}