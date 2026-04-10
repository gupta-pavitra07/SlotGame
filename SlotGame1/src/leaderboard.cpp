#include "../include/leaderboard.h"
#include <iostream>
#include <algorithm>

using namespace std;

void Leaderboard::addPlayer(Player p) 
{
    players.push_back(p);
}

bool comparePlayers(Player a, Player b) 
{
    return a.getBalance() > b.getBalance();
}


void Leaderboard::sortPlayers() 
{
    sort(players.begin(), players.end(), comparePlayers);
}


void Leaderboard::display() 
{
    cout << "\n--- Leaderboard ---\n";

    if (players.empty()) {
        cout << "No players available.\n";
        return;
    }

    int rank = 1;
    for (auto p : players) {
        cout << rank << ". "
             << p.getName()
             << " : ₹"
             << p.getBalance() << endl;
        rank++;
    }
}