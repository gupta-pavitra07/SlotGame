#include "../include/file.h"
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

vector<Player> loadPlayers()
{
    vector<Player> players;
    ifstream file("/Users/pavitragupta/DAAPBL/SlotGame/data/players.txt");
    string line;

    while (getline(file, line))
    {
        if (line.empty()) continue;
        
        istringstream iss(line);
        string name, password, lastQuizDate = "";
        double balance;
        int wins = 0, totalSpins = 0, totalPredictions = 0, quizzesAttempted = 0;
        double totalCoinsWon = 0, largestWin = 0;

        if (iss >> name >> password >> balance >> wins >> totalSpins >> totalPredictions >> totalCoinsWon >> largestWin >> quizzesAttempted >> lastQuizDate)
        {
            Player p(name, balance, password, wins, totalSpins, totalPredictions, totalCoinsWon, largestWin, quizzesAttempted, lastQuizDate);
            players.push_back(p);
        }
        else
        {
            iss.clear();
            iss.str(line);
            if (iss >> name >> password >> balance >> wins >> totalSpins >> totalPredictions >> totalCoinsWon >> largestWin)
            {
                Player p(name, balance, password, wins, totalSpins, totalPredictions, totalCoinsWon, largestWin, 0, "");
                players.push_back(p);
            }
            else
            {
                iss.clear();
                iss.str(line);
                if (iss >> name >> password >> balance >> wins)
                {
                    Player p(name, balance, password, wins);
                    players.push_back(p);
                }
                else
                {
                    iss.clear();
                    iss.str(line);
                    if (iss >> name >> password >> balance)
                    {
                        Player p(name, balance, password, 0);
                        players.push_back(p);
                    }
                }
            }
        }
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
            pl = p;  
            found = true;
            break;
        }
    }

    if (!found)
        players.push_back(p);

    std::filesystem::create_directories("/Users/pavitragupta/DAAPBL/SlotGame/data");
    ofstream file("/Users/pavitragupta/DAAPBL/SlotGame/data/players.txt"); 

    for (auto &pl : players)
    {
        file << pl.getName() << " " << pl.getPassword() << " " << pl.getBalance() << " " << pl.getWins() << " " 
             << pl.getTotalSpins() << " " << pl.getTotalPredictions() << " " << pl.getTotalCoinsWon() << " " << pl.getLargestWin() << " "
             << pl.getQuizzesAttempted() << " " << (pl.getLastQuizDate().empty() ? "NONE" : pl.getLastQuizDate()) << endl;
    }

    file.close();
}