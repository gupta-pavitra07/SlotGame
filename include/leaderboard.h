#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "player.h"
#include <vector>
using namespace std;

class Leaderboard {
private:
    vector<Player> players;

public:
    void addPlayer(Player p);
    void sortPlayers();
    void display();
};

#endif