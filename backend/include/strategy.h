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
    static std::string suggestgreedy(double totalAmount);
    static std::string suggestdp(int budget);
};

#endif