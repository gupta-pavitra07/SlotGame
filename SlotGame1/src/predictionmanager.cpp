#include "../include/predictionmanager.h"
#include <iostream>

using namespace std;

vector<Prediction> PredictionManager::takePredictions(double totalAmount) {

    vector<Prediction> predictions;
    double remaining = totalAmount;

    cout << "\n--- Make Your Predictions ---\n";

    while (remaining > 0) {

        cout << "\nRemaining Amount: ₹" << remaining << endl;

        Prediction p;
        int choice;

        cout << "Choose Prediction Type:\n";
        cout << "1. Exact Prediction (🍒 💎 ⭐️)\n";
        cout << "2. Symbol Prediction(🍒,⭐️,💎,7️⃣,🔔)\n";
        cout << "3. Pattern Prediction\n";
        cout << "0. Done\n";

        cin >> choice;

        if (choice == 0) break;

        cout << "Enter amount: ";
        cin >> p.amount;

        if (p.amount > remaining) {
            cout << "Not enough remaining amount!\n";
            continue;
        }

        p.type = (PredictionType)choice;

        if (p.type == EXACT) {
            cout << "Enter 3 symbols (e.g., CHERRY STAR BELL): ";
            cin >> p.s1 >> p.s2 >> p.s3;
        }

        else if (p.type == SYMBOL) {
            cout << "Enter symbol: ";
            cin >> p.symbol;
        }

        else if (p.type == PATTERN) {
            cout << "Enter pattern (ALL SAME SYMBOLS(ENTER: ALL) / TWO SAME SYMBOLS(ENTER: PAIR)): ";
            cin >> p.pattern;
        }

        predictions.push_back(p);
        remaining -= p.amount;
    }

    return predictions;
}