#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include <string>
using namespace std;

struct Option {
    string name;
    double probability;
    double multiplier;
};

class Strategy {
public:
    void suggestgreedy(double totalAmount);
};

#endif