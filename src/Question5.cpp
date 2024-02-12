#include <string>
#include <vector>

#include "func.h"
#include "Question2.h"
#include "Question3.h"
#include "Question4.h"

using std :: to_string;
using std :: vector;

int countChoice(const triplets &feasibleChoices) {
    int cnt = 0;
    for (vector<Choice> choices : feasibleChoices) cnt += choices.size();
    return cnt;
}

vector<Instance> processInstances(int number, bool analysis) {
    vector<Instance> instances;
    for (int i = 0; i < number; ++i) {
        instances.push_back(readInstance(&("data/test" + to_string(i + 4) + ".txt")[0]));
        if (analysis) printf("Instance %d:\n", i + 1);
        sortFeasibleSolutions(instances[i]);
        if (analysis) printf("Total triplet numbers initially: %d.\n", countChoice(instances[i].feasibleChoices));
        preprocessing(instances[i]);
        if (instanceNoSolution(instances[i])) {
            if (analysis) printf("Instance no solution.\n\n");
            continue;
        }
        if (analysis) printf("Total triplet numbers after step 1: %d.\n", countChoice(instances[i].feasibleChoices));
        removeIPDominated(instances[i]);
        if (analysis) printf("Total triplet numbers after step 2: %d.\n", countChoice(instances[i].feasibleChoices));
        removeLPDominated(instances[i]);
        if (analysis) printf("Total triplet numbers after step 3: %d.\n\n", countChoice(instances[i].feasibleChoices));
    }
    return instances;
}

// int main() {
//     vector<Instance> instances = processInstances(5, true);
//     return 0;
// }