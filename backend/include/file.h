#ifndef FILE_H
#define FILE_H

#include "player.h"
#include <vector>
using namespace std;

void savePlayer(Player p);
vector<Player> loadPlayers();

#endif