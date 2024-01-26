#include <vector>
#include <utility>

#include "func.h"

using std :: vector;

bool instanceNoSolution(int channelNumber, int choiceNumber, int userNumber, int totalEnergy, const vector<vector<vector<int>>>& powerMatrices, const vector<vector<vector<int>>>& rateMatrices);

void preprocessing(int channelNumber, int choiceNumber, int userNumber, int totalEnergy, triplets& feasibleChoices);