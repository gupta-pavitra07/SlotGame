#include "../include/predictionevaluator.h"
#include <map>

using namespace std;

double PredictionEvaluator::evaluateAll(vector<Prediction>& predictions, vector<string>& result)
{
    double totalReward = 0;

    for (auto &p : predictions)
    {
        // EXACT MATCH
        if (p.type == EXACT)
        {
            if (p.s1 == result[0] &&
                p.s2 == result[1] &&
                p.s3 == result[2])
            {
                totalReward += p.amount * 10;
                continue;
            }
        }

        // SYMBOL MATCH (FIXED)
        if (p.type == SYMBOL)
        {
            for (string s : result)
            {
                if (s == p.symbol)
                {
                    totalReward += p.amount * 1.2;
                    break;
                }
            }
        }

        // PATTERN
        if (p.type == PATTERN)
        {
            map<string, int> freq;

            for (string s : result)
                freq[s]++;

            bool isAllSame = false;
            bool isPair = false;

            for (auto f : freq)
            {
                if (f.second == 3) isAllSame = true;
                if (f.second == 2) isPair = true;
            }

            if (p.pattern == "ALL" && isAllSame)
                totalReward += p.amount * 5;

            else if (p.pattern == "PAIR" && isPair)
                totalReward += p.amount * 2;
        }
    }

    return totalReward;
}