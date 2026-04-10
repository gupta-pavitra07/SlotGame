#ifndef PREDICTION_H
#define PREDICTION_H

#include <string>
using namespace std;

enum PredictionType {
    EXACT = 1,
    SYMBOL,
    PATTERN
};

struct Prediction {
    PredictionType type;
    double amount;

    string s1, s2, s3;

    string symbol;

    string pattern; 
};

#endif