#include "../include/search.h"

int Search::linearSearch(vector<Player>& players, string name) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].getName() == name) {
            return i;
        }
    }
    return -1;
}