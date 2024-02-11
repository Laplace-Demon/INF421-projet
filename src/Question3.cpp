#include <vector>
#include <utility>
#include <algorithm>

#include "func.h"

using std :: vector;
using std :: pair;
using std :: sort;

void removeReversedPair(vector<Choice>& array) {
    int lastRate = 0;
    vector<Choice> answer;
    for (Choice temp : array) {
        if (temp.rate <= lastRate) continue;
        answer.push_back(temp);
        lastRate = temp.rate;
    }
    array = answer;
}

void sortFeasibleSolutions(Instance &instance) {
    for (int i = 0; i < instance.channelNumber; ++i)
        sort(instance.feasibleChoices[i].begin(), instance.feasibleChoices[i].end());
}

void removeIPDominated(Instance &instance) {
    for (int i = 0; i < instance.channelNumber; ++i)
        removeReversedPair(instance.feasibleChoices[i]);
}