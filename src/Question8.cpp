#include <algorithm>

#include "func.h"

using std :: reverse;

ILPSolution DPSolveILP(Instance instance) {
/*
    dp[n][p] = min{dp[n - 1][n - p_k,m,n] + r_k,m,n}
*/
    vector<vector<int>> maximumRate(instance.channelNumber, vector<int>(instance.totalEnergy + 1, 0));
    for (int i = 1, pos = instance.feasibleChoices[0][0].cost; i < instance.feasibleChoices[0].size(); ++i) {
        for (; pos <= instance.feasibleChoices[0][i].cost; ++pos) maximumRate[0][pos] = instance.feasibleChoices[0][i - 1].rate;
    }
    for (int i = 1; i < instance.channelNumber; ++i)
        for (int j = 1; j <= instance.totalEnergy; ++j)
            for (Choice temp : instance.feasibleChoices[i])
                maximumRate[i][j] = max(maximumRate[i - 1][j - temp.cost] + temp.rate, maximumRate[i][j]);
    
    ILPSolution solution;
    int currentEnergy = instance.totalEnergy;
    for (int i = instance.channelNumber - 1, &j = instance.totalEnergy; i > 0; --i) {
        for (Choice temp : instance.feasibleChoices[i]) {
            if (maximumRate[i][j] == maximumRate[i - 1][j - temp.cost] + temp.rate) {
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