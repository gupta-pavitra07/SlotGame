#include "../include/file.h"
#include <fstream>

using namespace std;

vector<Player> loadPlayers()
{
    vector<Player> players;
    ifstream file("players.txt");

    string name;
    double balance;

    while (file >> name >> balance)
    {
        Player p(name, balance);
        players.push_back(p);
    }

    file.close();
    return players;
}

void savePlayer(Player p)
{
    vector<Player> players = loadPlayers();

    bool found = false;

    for (auto &pl : players)
    {
        if (pl.getName() == p.getName())
        {
            pl = p;   // ✅ update existing player
            found = true;
            break;
        }
    }

    if (!found)
        players.push_back(p);

    ofstream file("players.txt");  // ✅ overwrite file

    for (auto &pl : players)
    {
        file << pl.getName() << " " << pl.getBalance() << endl;
    }

    file.close();
}