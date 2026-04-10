#include "../include/file.h"
#include <fstream>
#include <sstream>

using namespace std;

void savePlayer(Player p) {
    ofstream file("data/players.txt", ios::app);

    file << p.getName() << " " << p.getBalance() << endl;

    file.close();
}

vector<Player> loadPlayers() {
    vector<Player> players;
    ifstream file("data/players.txt");

    string name;
    double balance;

    while (file >> name >> balance) {
        Player p(name, balance);
        players.push_back(p);
    }

    file.close();
    return players;
}