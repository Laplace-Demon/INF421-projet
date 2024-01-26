#include <vector>
#include <utility>
#include <cstdio>

using std :: vector;
using std :: pair;
using std :: make_pair;

void readInt(int& n) {
    double temp;
    scanf("%lf", &temp);
    n = (int)temp;
}

void readInput(int& channelNumber, int& choiceNumber, int& userNumber, int& totalEnengy, vector<vector<vector<int>>>& powerMatrices, vector<vector<vector<int>>>& rateMatrices) {
    readInt(channelNumber);
    readInt(choiceNumber);
    readInt(userNumber);
    readInt(totalEnengy);
    vector<vector<vector<int>>> tempPowerMatrices(channelNumber, vector<vector<int>>(userNumber, vector<int>(choiceNumber)));
    vector<vector<vector<int>>> tempRateMatrices(channelNumber, vector<vector<int>>(userNumber, vector<int>(choiceNumber)));
    for (int i = 0; i < channelNumber; ++i)
        for (int j = 0; j < userNumber; ++j)
            for (int k = 0; k < choiceNumber; ++k)
                readInt(tempPowerMatrices[i][j][k]);
    for (int i = 0; i < channelNumber; ++i)
        for (int j = 0; j < userNumber; ++j)
            for (int k = 0; k < choiceNumber; ++k)
                readInt(tempRateMatrices[i][j][k]);
    powerMatrices = tempPowerMatrices;
    rateMatrices = tempRateMatrices;
}

typedef vector<vector<pair<int, int>>> triplets;

triplets matrices2triplet(int channelNumber, int choiceNumber, int userNumber, int totalEnergy, const vector<vector<vector<int>>>& powerMatrices, const vector<vector<vector<int>>>& rateMatrices) {
    triplets feasibleChoices = vector<vector<pair<int, int>>>(channelNumber);
    for (int i = 0; i < channelNumber; ++i)
        for (int j = 0; j < userNumber; ++j)
            for (int k = 0; k < choiceNumber; ++k)
                feasibleChoices[i].push_back(make_pair(powerMatrices[i][j][k], rateMatrices[i][j][k]));
    return feasibleChoices;
}
