#include <vector>
#include <string>
#include <utility>
#include <optional>

using std :: vector;
using std :: string;
using std :: pair;
using std :: optional;

#ifndef FUNC

#define FUNC

inline int min(int a, int b) {
    return a < b ? a : b;
}

inline int max(int a, int b) {
    return a > b ? a : b;
}

void readInput(int& channelNumber, int& choiceNumber, int& userNumber, int& totalEnengy, vector<vector<vector<int>>>& powerMatrices, vector<vector<vector<int>>>& rateMatrices);

struct Choice {
    int cost, rate, user;

    Choice (int cost, int rate, int user) : cost(cost), rate(rate), user(user) { }
};

typedef vector<vector<Choice>> triplets;

triplets matrices2triplet(int channelNumber, int choiceNumber, int userNumber, int totalEnergy, const vector<vector<vector<int>>>& powerMatrices, const vector<vector<vector<int>>>& rateMatrices);

inline bool
operator<(const Choice& lhs, const Choice& rhs) {
    return lhs.cost < rhs.cost;
}

struct Instance {
    int channelNumber, choiceNumber, userNumber, totalEnergy;
    vector<vector<vector<int>>> powerMatrices, rateMatrices;
    triplets feasibleChoices;
};

Instance readInstance(string inputPath);

struct LPSolution {
    vector<Choice> solution;
    optional<pair<pair<int, double>, Choice>> fractional;
};

struct ILPSolution {
    vector<Choice> solution;
};

#endif