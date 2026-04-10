#include <iostream>
#include <ctime>
#include "player.h"
#include "slot.h"
#include "strategy.h"
#include "leaderboard.h"
#include "file.h"
#include "search.h"
#include "predictionmanager.h"
#include "predictionevaluator.h"

using namespace std;

int main() {

    srand(time(0));

    string name;
    double balance;

    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter starting balance: ";
    cin >> balance;

    Player player(name, balance);
    SlotMachine slot;
    Strategy strategy;
    Leaderboard lb;
    PredictionManager predictionManager;
    PredictionEvaluator evaluator2;
    Search search;

    cout << "\nWelcome\n " << player.getName();

    char choice;

    do {
        double stakeAmount;

        cout << "\nEnter amount to use: ";
        cin >> stakeAmount;

        if (stakeAmount > player.getBalance()) 
        {
            cout << "Not enough balance!\n";
            continue;
        }

        strategy.suggestgreedy(stakeAmount);

        vector<Prediction> predictions = predictionManager.takePredictions(stakeAmount);

        player.deductBalance(stakeAmount);

        vector<string> result = slot.spin();
        slot.displaySpin(result);

        double totalReward = evaluator2.evaluateAll(predictions, result);
        player.addBalance(totalReward);
        if (totalReward > 0)
            cout << "Total Reward: ₹" << totalReward << endl;
        else
            cout << "No prediction matched.\n";

        cout << "Updated Balance: ₹" << player.getBalance() << endl;

        cout << "\nContinue? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    savePlayer(player);

    vector<Player> allPlayers = loadPlayers();
    for (auto p : allPlayers) {
        lb.addPlayer(p);
    }
    lb.sortPlayers();
    lb.display();

    string searchName;
    cout << "\nEnter name to search: ";
    cin >> searchName;

    int index = search.linearSearch(allPlayers, searchName);

    if (index != -1) 
    {
        cout << "Player Found: "
             << allPlayers[index].getName()
             << " Balance: ₹"
             << allPlayers[index].getBalance() << endl;
             //allPlayers[index].showHistory();
             
    }
    else 
    {
        cout << "Player not found.\n";
    }
    cout << "\nThank you for using the system!\n";
    return 0;
}