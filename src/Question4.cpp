#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

#include "func.h"

using std :: vector;
using std :: pair;
using std :: reverse;
using std :: stack;

bool LPDominatedAtHead(stack<pair<int, int>> feasibleChoices, pair<int, int> nextChoice) {
    if (feasibleChoices.size() <= 1) return false;
    pair<int, int> currentChoice = feasibleChoices.top();
    feasibleChoices.pop();
    pair<int, int> lastChoice = feasibleChoices.top();
    return (nextChoice.second - currentChoice.second) * (currentChoice.first - lastChoice.first) >= \
           (currentChoice.second - lastChoice.second) * (nextChoice.first - currentChoice.first);
}

void removeLPDominated(int channelNumber, triplets& feasibleChoices) {
    for (int i = 0; i < channelNumber; ++i) {
        stack<pair<int, int>> newFeasibleChoices;
        for (int j = 1; j < feasibleChoices[i].size(); ++j) {
            while (LPDominatedAtHead(newFeasibleChoices, feasibleChoices[i][j])) newFeasibleChoices.pop();
            newFeasibleChoices.push(feasibleChoices[i][j]);
        }
        feasibleChoices[i].clear();
        while (!newFeasibleChoices.empty()) {
            feasibleChoices[i].push_back(newFeasibleChoices.top());
            newFeasibleChoices.pop();
        }
        reverse(feasibleChoices[i].begin(), feasibleChoices[i].end());
    }
}