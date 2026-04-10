#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
using namespace std;

class Player
{
    private:
    string name;
    double balance ;
    vector<string> history;

    public:
    Player(string name , double balance);

    string getName();
    double getBalance();

    void addBalance(double amount);
    void deductBalance(double amount);

    void addHistory(string record);
    void showHistory();

};
#endif