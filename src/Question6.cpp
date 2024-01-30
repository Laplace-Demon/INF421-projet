#include <vector>
#include <queue>
#include <utility>
#include <optional>

#include "func.h"

using std :: vector;
using std :: priority_queue;
using std :: pair;
using std :: make_pair;

double calculateIncrementalEfficiency(int pos, const vector<Choice>& feasibleChoices) {
    return ((double)feasibleChoices[pos + 1].rate - (double)feasibleChoices[pos].rate) /
           ((double)feasibleChoices[pos + 1].cost - (double)feasibleChoices[pos].cost);
}

LPSolution greedySolveLP(const Instance& instance) {
    int remainEnergy = instance.totalEnergy;
    vector<int> currentChoices;
    priority_queue<pair<double, int>> possibleChoices;

    for (int i = 0; i < instance.channelNumber; ++i) {
        remainEnergy -= instance.feasibleChoices[i][0].cost;
        currentChoices.push_back(0);
        if (instance.feasibleChoices[i].size() > currentChoices[i]) possibleChoices.push(make_pair(calculateIncrementalEfficiency(currentChoices[i], instance.feasibleChoices[i]), i));
    }
    
    LPSolution solution;
    while (!possibleChoices.empty()) {
        pair<double, int> greedyChoice = possibleChoices.top();
        int currentChannel = greedyChoice.second;
        possibleChoices.pop();
        if (remainEnergy >= instance.feasibleChoices[currentChannel][currentChoices[currentChannel] + 1].cost) {
            remainEnergy -= instance.feasibleChoices[currentChannel][currentChoices[currentChannel] + 1].cost;
            currentChoices[currentChannel] += 1;
            if (remainEnergy == 0) {
                for (int i = 0; i < instance.channelNumber; ++i) solution.solution.push_back(Choice(instance.feasibleChoices[i][currentChoices[i]].cost, instance.feasibleChoices[i][currentChoices[i]].rate, instance.feasibleChoices[i][currentChoices[i]].user));
                solution.fractional = optional<pair<pair<int, double>, Choice>>();
                break;
            }
            if (instance.feasibleChoices[currentChannel].size() > currentChoices[currentChannel]) possibleChoices.push(make_pair(calculateIncrementalEfficiency(currentChoices[currentChannel], instance.feasibleChoices[currentChannel]), currentChannel));
        }
        else {
            for (int i = 0; i < instance.channelNumber; ++i) solution.solution.push_back(Choice(instance.feasibleChoices[i][currentChoices[i]].cost, instance.feasibleChoices[i][currentChoices[i]].rate, instance.feasibleChoices[i][currentChoices[i]].user));
            solution.fractional = optional<pair<pair<int, double>, Choice>>(make_pair(make_pair(currentChannel, (double)remainEnergy / ((double)instance.feasibleChoices[currentChannel][currentChoices[currentChannel] + 1].cost - (double)instance.feasibleChoices[currentChannel][currentChoices[currentChannel]].cost)),
                                  Choice(instance.feasibleChoices[currentChannel][currentChoices[currentChannel] + 1].cost, instance.feasibleChoices[currentChannel][currentChoices[currentChannel] + 1].rate,
                                  instance.feasibleChoices[currentChannel][currentChoices[currentChannel] + 1].user)));
            break;
        }
    }

    return solution;
}