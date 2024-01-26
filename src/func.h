#include <vector>
#include <utility>

using std :: vector;
using std :: pair;

inline int min(int a, int b) {
    return a < b ? a : b;
}

void readInput(int& channelNumber, int& choiceNumber, int& userNumber, int& totalEnengy, vector<vector<vector<int>>>& powerMatrices, vector<vector<vector<int>>>& rateMatrices);

typedef vector<vector<pair<int, int>>> triplets;

triplets matrices2triplet(int channelNumber, int choiceNumber, int userNumber, int totalEnergy, const vector<vector<vector<int>>>& powerMatrices, const vector<vector<vector<int>>>& rateMatrices);