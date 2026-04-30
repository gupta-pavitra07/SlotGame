#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
using namespace std;

#include <string>
class Player
{
    private:
    string name;
    double balance ;
    string password;
    int wins;
    int totalSpins;
    int totalPredictions;
    double totalCoinsWon;
    double largestWin;
    int quizzesAttempted;
    string lastQuizDate;
    vector<std::string> history;

    public:
    Player(string name , double balance, string password = "", int wins = 0, int totalSpins = 0, int totalPredictions = 0, double totalCoinsWon = 0, double largestWin = 0, int quizzesAttempted = 0, string lastQuizDate = "");

    string getName();
    double getBalance() const;
    string getPassword();
    int getWins() const;
    int getTotalSpins() const;
    int getTotalPredictions() const;
    double getTotalCoinsWon() const;
    double getLargestWin() const;
    int getQuizzesAttempted() const;
    string getLastQuizDate() const;

    void addBalance(double amount);
    void deductBalance(double amount);
    void addWin();
    void incrementSpins();
    void addPredictions(int count);
    void updateWinStats(double coinsWon);
    void attemptQuiz(string currentDate);

    void addHistory(string record);
    void showHistory();

};
#endif