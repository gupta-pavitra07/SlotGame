#include "../include/strategy.h"
#include "../include/probability.h"
#include "../include/slot.h"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

void Strategy::suggestgreedy(double totalAmount) {

    Probability prob;
    SlotMachine slot;

    map<string, double> probs = slot.getSymbolProbabilities();

    double exactP = prob.exactMatchProb();

    double bestSymbolProb = 0;
    for (auto &p : probs) {
        bestSymbolProb = max(bestSymbolProb, p.second);
    }

    double symbolP = prob.symbolMatchProb(bestSymbolProb);
    double allSameP = prob.allSameProb();
    double pairP = prob.pairProb();

    vector<Option> options = {
        {"Exact Match", exactP, 10},
        {"Symbol Match", symbolP, 1.2},
        {"All Same Symbols", allSameP, 5},
        {"Two Same Symbols", pairP, 3}
    };

    double bestEV = 0;
    string bestOption;

    for (auto &op : options) {
        double ev = op.probability * op.multiplier;

        if (ev > bestEV) {
            bestEV = ev;
            bestOption = op.name;
        }
    }

    cout << "\n--- Strategy Suggestion ---\n";
    cout << "You may consider focusing on: " << bestOption << endl;
}
