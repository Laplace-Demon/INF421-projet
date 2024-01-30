#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

#include "func.h"

using std :: vector;
using std :: pair;
using std :: reverse;
using std :: stack;

bool LPDominatedAtHead(stack<Choice> feasibleChoices, Choice nextChoice) {
    if (feasibleChoices.size() <= 1) return false;
    Choice currentChoice = feasibleChoices.top();
    feasibleChoices.pop();
    Choice lastChoice = feasibleChoices.top();
    return (nextChoice.rate - currentChoice.rate) * (currentChoice.cost - lastChoice.cost) >=
           (currentChoice.rate - lastChoice.rate) * (nextChoice.cost - currentChoice.cost);
}

void removeLPDominated(Instance instance) {
    for (int i = 0; i < instance.channelNumber; ++i) {
        stack<Choice> newFeasibleChoices;
        for (int j = 1; j < instance.feasibleChoices[i].size(); ++j) {
            while (LPDominatedAtHead(newFeasibleChoices, instance.feasibleChoices[i][j])) newFeasibleChoices.pop();
            newFeasibleChoices.push(instance.feasibleChoices[i][j]);
        }
        instance.feasibleChoices[i].clear();
        while (!newFeasibleChoices.empty()) {
            instance.feasibleChoices[i].push_back(newFeasibleChoices.top());
            newFeasibleChoices.pop();
        }
        reverse(instance.feasibleChoices[i].begin(), instance.feasibleChoices[i].end());
    }
}