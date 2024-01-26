#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

#include "func.h"

using std :: vector;
using std :: pair;
using std :: reverse;
using std :: stack;

bool LPDominated(stack<pair<int, int>> newFeasibleChoices, pair<int, int>) {

}

void removeLPDominated(int channelNumber, triplets& feasibleChoices) {
    for (int i = 0; i < channelNumber; ++i) {
        stack<pair<int, int>> newFeasibleChoices;
        for (int j = 1; j < feasibleChoices[i].size(); ++j) {
            while () newFeasibleChoices.pop();
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