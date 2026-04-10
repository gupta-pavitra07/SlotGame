#ifndef PREDICTIONEVALUATOR_H
#define PREDICTIONEVALUATOR_H

#include "prediction.h"
#include <vector>
#include <string>
using namespace std;

class PredictionEvaluator {
public:
    double evaluateAll(vector<Prediction>& predictions, vector<string>& result);
};

#endif