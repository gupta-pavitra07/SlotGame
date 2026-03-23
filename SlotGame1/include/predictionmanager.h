#ifndef PREDICTIONMANAGER_H
#define PREDICTIONMANAGER_H

#include "prediction.h"
#include <vector>
using namespace std;

class PredictionManager {
public:
    vector<Prediction> takePredictions(double totalAmount);
};

#endif