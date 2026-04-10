#ifndef SEARCH_H
#define SEARCH_H

#include "player.h"
#include <vector>
using namespace std;

class Search 
{
public:
    int linearSearch(vector<Player>& players, string name);
};

#endif