#include "../include/player.h"
#include <iostream>
using namespace std;

Player::Player(string name, double balance) 
{
    this->name = name;
    this->balance = balance;
}

string Player::getName() 
{
    return name;
}

double Player::getBalance() 
{
    return balance;
}

void Player::addBalance(double amount) 
{
    balance += amount;
}

void Player::deductBalance(double amount) 
{
    balance -= amount;
}

void Player::addHistory(string record) 
{
    history.push_back(record);
}

void Player::showHistory() 
{
    cout << "\nGame History:\n";
    for (string h : history) {
        cout << h << endl;
    }
}