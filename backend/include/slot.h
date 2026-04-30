#ifndef SLOT_H
#define SLOT_H

#include <vector>
#include <string>
#include <map>
using namespace std;

class SlotMachine
{
    private: 
    vector<string>symbols;

    public:
    SlotMachine();
    vector<string> spin();
    void displaySpin(vector<string> result);
    map<string, double> getSymbolProbabilities();
};

#endif


