#include <vector>
#include <utility>

#include "func.h"

using std :: vector;
using std :: make_pair;

bool instanceNoSolution(int channelNumber, int choiceNumber, int userNumber, int totalEnergy, const vector<vector<vector<int>>>& powerMatrices, const vector<vector<vector<int>>>& rateMatrices) {
    int minimumTotalEnergy = 0;
    for (int i = 0; i < channelNumber; ++i) {
        int minimumEnergy = 0x3f3f3f3f;
        for (int j = 0; j < userNumber; ++j)
            minimumEnergy = min(minimumEnergy, powerMatrices[i][j][0]);
        minimumTotalEnergy += minimumEnergy;
    }
    return minimumTotalEnergy > totalEnergy;
}

void preprocessing(int channelNumber, int choiceNumber, int userNumber, int totalEnergy, triplets& feasibleChoices) {
    int minimumTotalEnergy = 0; 
    triplets newFeasibleChoices = vector<vector<pair<int, int>>>(channelNumber);
    vector<int> minimumEnergies(channelNumber);
    for (int i = 0; i < channelNumber; ++i) {
        int minimumEnergy = 0x3f3f3f3f;
        for (pair<int, int> temp : feasibleChoices[i])
            minimumEnergy = min(minimumEnergy, temp.first);
        minimumEnergies[i] = minimumEnergy;
        minimumTotalEnergy += minimumEnergy;
    }
    for (int i = 0; i < channelNumber; ++i) {
        for (pair<int, int> temp : feasibleChoices[i]) {
            if (totalEnergy < minimumTotalEnergy - minimumEnergies[i] + temp.first) continue;
            newFeasibleChoices[i].push_back(temp);
        }
    }
    feasibleChoices = newFeasibleChoices;
}