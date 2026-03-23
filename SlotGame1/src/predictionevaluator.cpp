#include "../include/predictionevaluator.h"
#include <iostream>
#include <map>

using namespace std;

double PredictionEvaluator::evaluateAll(vector<Prediction>& predictions, vector<string>& result) {

    double totalReward = 0;

    for (auto &p : predictions) {


        if (p.type == EXACT) {

            if (p.s1 == result[0] && p.s2 == result[1] && p.s3 == result[2]) {
                double reward = p.amount * 10; 
                cout << "Exact Prediction WIN → ₹" << reward << endl;
                totalReward += reward;
            }
        }


        else if (p.type == SYMBOL) {

            bool found = false;

            for (string s : result) {
                if (s == p.symbol) {
                    found = true;
                    break;
                }
            }

            if (found) {
                double reward = p.amount * 1.5;
                cout << "Symbol Prediction WIN → ₹" << reward << endl;
                totalReward += reward;
            }
        }


        else if (p.type == PATTERN) {

            map<string, int> freq;

            for (string s : result) {
                freq[s]++;
            }

            bool isAllSame = false;
            bool isPair = false;

            for (auto f : freq) {
                if (f.second == 3) isAllSame = true;
                if (f.second == 2) isPair = true;
            }

            if (p.pattern == "ALL" && isAllSame) {
                double reward = p.amount * 5;
                cout << "Pattern ALL WIN → ₹" << reward << endl;
                totalReward += reward;
            }

            else if (p.pattern == "PAIR" && isPair) {
                double reward = p.amount * 2;
                cout << "Pattern PAIR WIN → ₹" << reward << endl;
                totalReward += reward;
            }
        }
    }

    return totalReward;
}