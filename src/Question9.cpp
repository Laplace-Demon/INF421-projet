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

    int pos1 = 0;
    for (int i = 0; i <= rateUpperBound; ++i) {
        while (instance.feasibleChoices[0][pos1].rate < i) ++pos1;
        if (pos1 == instance.channelNumber) break;
        minimalPower[0][i] = instance.feasibleChoices[0][pos1].cost;
    }

    for (int i = 1; i < instance.channelNumber; ++i)
        for (int j = 0; j <= rateUpperBound; ++j)
            for (Choice temp : instance.feasibleChoices[i])
                minimalPower[i][j] = min(minimalPower[i - 1][j - temp.rate] + temp.cost, minimalPower[i][j]);
    
    ILPSolution solution;
    int currentRate = 0;
    return solution;
}