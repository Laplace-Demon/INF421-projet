#include <vector>
#include <utility>
#include <algorithm>

#include "func.h"

using std :: vector;
using std :: pair;
using std :: sort;

void removeReversedPair(vector<pair<int, int>>& array) {
    int lastValue = 0;
    vector<pair<int, int>> answer;
    for (pair<int, int> temp : array) {
        if (temp.second <= lastValue) continue;
        answer.push_back(temp);
        lastValue = temp.second;
    }
    array = answer;
}

void sortFeasibleSolutions(int channelNumber, triplets& feasibleChoices) {
    for (int i = 0; i < channelNumber; ++i)
        sort(feasibleChoices[i].begin(), feasibleChoices[i].end());
}

void removeIPDominated(int channelNumber, triplets& feasibleChoices) {
    for (int i = 0; i < channelNumber; ++i)
        removeReversedPair(feasibleChoices[i]);
}