#include <cstdio>
#include <fstream>

#include "func.h"

using std :: vector;
using std :: pair;
using std :: make_pair;
using std :: ifstream;

triplets matrices2triplet(int channelNumber, int choiceNumber, int userNumber, int totalEnergy, const vector<vector<vector<int>>>& powerMatrices, const vector<vector<vector<int>>>& rateMatrices) {
    triplets feasibleChoices = vector<vector<Choice>>(channelNumber);
    for (int i = 0; i < channelNumber; ++i)
        for (int j = 0; j < userNumber; ++j)
            for (int k = 0; k < choiceNumber; ++k)
                feasibleChoices[i].push_back(Choice(powerMatrices[i][j][k], rateMatrices[i][j][k], j));
    return feasibleChoices;
}

Instance readInstance(char *inputPath) {
    ifstream input(inputPath);
    double channelNumber, choiceNumber, userNumber, totalEnergy;
    input >> channelNumber >> choiceNumber >> userNumber >> totalEnergy;
    vector<vector<vector<int>>> tempPowerMatrices(channelNumber, vector<vector<int>>(userNumber, vector<int>(choiceNumber)));
    vector<vector<vector<int>>> tempRateMatrices(channelNumber, vector<vector<int>>(userNumber, vector<int>(choiceNumber)));
    double temp;
    for (int i = 0; i < channelNumber; ++i)
        for (int j = 0; j < userNumber; ++j)
            for (int k = 0; k < choiceNumber; ++k) {
                input >> temp;
                tempPowerMatrices[i][j][k] = temp;
            }
    for (int i = 0; i < channelNumber; ++i)
        for (int j = 0; j < userNumber; ++j)
            for (int k = 0; k < choiceNumber; ++k) {
                input >> temp;
                tempRateMatrices[i][j][k] = temp;
            }
    Instance instance(channelNumber, choiceNumber, userNumber, totalEnergy, tempPowerMatrices, tempRateMatrices, matrices2triplet(channelNumber, choiceNumber, userNumber, totalEnergy, tempPowerMatrices, tempRateMatrices));
    return instance;
}

void printInstance(const Instance &instance, int number) {
    for (int i = 0; i < instance.channelNumber; ++i) {
        for (int j = 0; j < number && j < instance.feasibleChoices[i].size(); ++j) {
            printf("%d %d %d\n", instance.feasibleChoices[i][j].cost, instance.feasibleChoices[i][j].rate, instance.feasibleChoices[i][j].user);
        }
        printf("\n");
    }
}

void LPSolutionAnalysis(Instance instance, LPSolution solution) {
    if (solution.has_solution == false) {
        printf("No solution.\n\n");
        return;
    }
    double sumTransmitPower = 0, sumDataRate = 0;
    for (Choice choice : solution.solution) {
        sumTransmitPower += choice.cost;
        sumDataRate += choice.rate;
    }
    if (solution.fractional.has_value()) {
        int channel = solution.fractional.value().first.first;
        double coef = solution.fractional.value().first.second;
        sumDataRate += coef * (double)(solution.fractional.value().second.rate - solution.solution[channel].rate);
        sumTransmitPower += coef * (double)(solution.fractional.value().second.cost - solution.solution[channel].cost);
    }
    printf("Optimal rate: %f.\n", sumDataRate);
    printf("Used power: %f.\n", sumTransmitPower);
    printf("Total power budget: %f.\n\n", (double)instance.totalEnergy);
}

void LPSolverSolutionAnalysis(Instance instance, LPSolverSolution solution) {
    if (solution.has_solution == false) {
        printf("No solution.\n\n");
        return;
    }
    double sumTransmitPower = 0, sumDataRate = 0;
    for (pair<double, Choice> choice : solution.solution) {
        sumTransmitPower += choice.first * choice.second.cost;
        sumDataRate += choice.first * choice.second.rate;
    }

    printf("Optimal rate: %f.\n", sumDataRate);
    printf("Used power: %f.\n", sumTransmitPower);
    printf("Total power budget: %f.\n\n", (double)instance.totalEnergy);
}