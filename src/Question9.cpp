#include <algorithm>

#include "func.h"

using std :: reverse;

ILPSolution anotherDPSolveILP(Instance instance) {
/*
    dp[n][r] = min{dp[n - 1][r - r_k,m,n] + p_k,m,n}
*/
    int rateUpperBound = 0;
    for (int i = 0; i < instance.channelNumber; ++i) rateUpperBound += instance.feasibleChoices[i][instance.feasibleChoices[i].size() - 1].rate;
    vector<vector<int>> minimalPower(instance.channelNumber, vector<int>(rateUpperBound + 1, 0));
    for (int i = 1; i < instance.feasibleChoices[0].size(); ++i) {
    }
    for (int i = 1; i < instance.channelNumber; ++i)
        for (int j = 1; j <= instance.totalEnergy; ++j)
            for (Choice temp : instance.feasibleChoices[i])
                minimalPower[i][j] = min(minimalPower[i - 1][j - temp.rate] + temp.cost, minimalPower[i][j]);
    
    ILPSolution solution;
    int currentEnergy = instance.totalEnergy;
    for (int i = instance.channelNumber - 1, &j = instance.totalEnergy; i > 0; --i) {
        for (Choice temp : instance.feasibleChoices[i]) {
            if (minimalPower[i][j] == minimalPower[i - 1][j - temp.cost] + temp.rate) {
                solution.solution.push_back(temp);
                j -= temp.cost;
                break;
            }
        }
    }
    int pos;
    for (pos = 0; pos < instance.feasibleChoices[0].size(); ++pos) {
        if (instance.feasibleChoices[0][pos].cost <= currentEnergy) continue;
    }
    pos -= 1;
    solution.solution.push_back(Choice(instance.feasibleChoices[0][pos]));
    reverse(solution.solution.begin(), solution.solution.end());
    return solution;
}