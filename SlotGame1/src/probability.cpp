#include "../include/probability.h"
#include <cmath>

using namespace std;


double Probability::exactMatchProb() 
{
    return 1.0 / 125.0;
}


double Probability::symbolMatchProb(double p) 
{
    return 1 - pow((1 - p), 3);
}


double Probability::allSameProb() 
{
    return 1.0 / 25.0;
}

double Probability::pairProb() 
{
    int favorable = 5 * 4 * 3;

    return (double)favorable / 125.0;
}