#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <string>
using namespace std;

class Probability 
{
public:
    double exactMatchProb();
    double symbolMatchProb(double p); 
    double allSameProb();
    double pairProb();
};

#endif