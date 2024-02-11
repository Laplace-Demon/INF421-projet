#include <vector>
#include <utility>

#include "func.h"

using std :: vector;
using std :: make_pair;

bool instanceNoSolution(const Instance &instance) {
    int minimumTotalEnergy = 0;
    for (int i = 0; i < instance.channelNumber; ++i) {
        int minimumEnergy = 0x3f3f3f3f;
        for (int j = 0; j < instance.userNumber; ++j) minimumEnergy = min(minimumEnergy, instance.powerMatrices[i][j][0]);
        minimumTotalEnergy += minimumEnergy;
    }
    return minimumTotalEnergy > instance.totalEnergy;
}

void preprocessing(Instance &instance) {
    int minimumTotalEnergy = 0; 
    triplets newFeasibleChoices = vector<vector<Choice>>(instance.channelNumber);
    vector<int> minimumEnergies(instance.channelNumber);
    for (int i = 0; i < instance.channelNumber; ++i) {
        int minimumEnergy = 0x3f3f3f3f;
        for (Choice temp : instance.feasibleChoices[i]) minimumEnergy = min(minimumEnergy, temp.cost);
        minimumEnergies[i] = minimumEnergy;
        minimumTotalEnergy += minimumEnergy;
    }
    for (int i = 0; i < instance.channelNumber; ++i) {
        for (Choice temp : instance.feasibleChoices[i]) {
            if (instance.totalEnergy < minimumTotalEnergy - minimumEnergies[i] + temp.cost) continue;
            newFeasibleChoices[i].push_back(temp);
        }
    }
    instance.feasibleChoices = newFeasibleChoices;
}