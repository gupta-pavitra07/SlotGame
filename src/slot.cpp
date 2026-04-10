#include "../include/slot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

SlotMachine::SlotMachine() {
    symbols = {"CHERRY", "STAR", "DIAMOND", "BELL", "7"};
    
}

vector<string> SlotMachine::spin() {
    
    vector<string> result;

    vector<pair<string, int>> weighted_sym = {
        {"CHERRY", 40},
        {"STAR", 25},
        {"DIAMOND", 20},
        {"BELL", 10},
        {"7", 5}
    };

    for (int i = 0; i < 3; i++) {
        int r = rand() % 100;
        int cumulative = 0;

        for (auto &sym : weighted_sym) {
            cumulative += sym.second;
            if (r < cumulative) {
                result.push_back(sym.first);
                break;
            }
        }
    }

    return result;
}

void SlotMachine::displaySpin(vector<string> result) {
    cout << "\nSlot Result: ";
    for (string s : result) {
        cout << s << " | ";
    }
    cout << endl;
}


map<string, double> SlotMachine::getSymbolProbabilities() {
    return {
        {"CHERRY", 0.40},
        {"STAR", 0.25},
        {"DIAMOND", 0.20},
        {"BELL", 0.10},
        {"7", 0.05}
    };
}
