#include "../include/strategy.h"
#include "../include/probability.h"
#include "../include/slot.h"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

std::string Strategy::suggestgreedy(double totalAmount) 
{

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

    std::string result = "Greedy Allocation for ₹" + std::to_string((int)totalAmount) + ":\n\n";
    result += "₹" + std::to_string((int)totalAmount) + " \u2192 " + bestOption + " (Highest EV)\n";
    return result;
}

std::string Strategy::suggestdp(int budget) 
    {
    Probability prob;
    SlotMachine slot;


    double exactEV = prob.exactMatchProb() * 10.0;
    double symbolEV = prob.symbolMatchProb(0.4) * 1.2;
    double patternAllEV = prob.allSameProb() * 5.0;
    double patternPairEV = prob.pairProb() * 3.0;

    // for dynamic variation
    auto perturb = []() {
        return 0.5 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / 1.0));
    };

    struct BetOption {
        std::string name;
        int cost;
        double value;
    };

    //  creating multiple "packages" for the 0/1 Knapsack
    // with dynamically perturbed expected values to vary suggestions.
    std::vector<BetOption> items = {
        {"exact", 40, (exactEV * 40) * perturb()},
        {"exact", 20, (exactEV * 20) * perturb()},
        {"exact", 10, (exactEV * 10) * perturb()},
        {"symbol", 30, (symbolEV * 30) * perturb()},
        {"symbol", 20, (symbolEV * 20) * perturb()},
        {"symbol", 10, (symbolEV * 10) * perturb()},
        {"pattern", 30, (patternAllEV * 30) * perturb()},
        {"pattern", 20, (patternAllEV * 20) * perturb()},
        {"pattern", 10, (patternPairEV * 10) * perturb()}
    };

    int n = items.size();
    vector<vector<double>> dp(n + 1,vector<double>(budget + 1, 0.0));

    // DP 0/1 Knapsack
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= budget; w++) 
        {
            if (items[i - 1].cost <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].cost] + items[i - 1].value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Backtracking
    vector<BetOption> chosen;
    int w = budget;
    for (int i = n; i > 0 && w > 0; i--) 
    {
        if (dp[i][w] != dp[i - 1][w]) {
            chosen.push_back(items[i - 1]);
            w -= items[i - 1].cost;
        }
    }


    map<string, int> allocations;
    for (const auto& item : chosen) 
    {
        allocations[item.name] += item.cost;
    }

    //leftover -> symbol (safe)
    int spent = 0;
    for (auto const& [key, val] : allocations) { spent += val; }
    if (spent < budget && budget >= 10) 
    {
        allocations["symbol"] += (budget - spent);
    }

    string result = "Budget: ₹" + to_string(budget) + "\n\n";
    for (const auto& pair : allocations) {
        result += "₹" + to_string(pair.second) + " \u2192 " + pair.first + "\n";
    }

    if (allocations.empty()) 
    {
        result += "Budget too small for any recommended bets.\n";
    }

    return result;
}
