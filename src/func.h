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
    Instance () {}
    Instance (int channelNumber, int choiceNumber, int userNumber, int totalEnergy, vector<vector<vector<int>>> powerMatrices, vector<vector<vector<int>>> rateMatrices, triplets feasibleChoices) {
        this->channelNumber = channelNumber;
        this->choiceNumber = choiceNumber;
        this->userNumber = userNumber;
        this->totalEnergy = totalEnergy;
        this->powerMatrices = powerMatrices;
        this->rateMatrices = rateMatrices;
        this->feasibleChoices = feasibleChoices;
    }
};

Instance readInstance(char *inputPath);

void printInstance(const Instance &instance, int number);

struct LPSolution {
    bool has_solution;
    vector<Choice> solution;
    optional<pair<pair<int, double>, Choice>> fractional;

    LPSolution() {
        this->has_solution = false;
    }
};

void LPSolutionAnalysis(Instance instance, LPSolution greedySolution);

struct ILPSolution {
    vector<Choice> solution;
};

#endif