#include <string>

#include "func.h"
#include "Question2.h"
#include "Question3.h"
#include "Question4.h"

using std :: to_string;

int countChoice(const triplets &feasibleChoices) {
    int cnt = 0;
    for (vector<Choice> choices : feasibleChoices) cnt += choices.size();
    return cnt;
}

int main() {
    Instance instances[5];
    for (int i = 0; i < 5; ++i) {
        instances[i] = readInstance(&("data/test" + to_string(i + 1) + ".txt")[0]);
        printf("Instance %d:\n", i + 1);
        sortFeasibleSolutions(instances[i]);
            //printInstance(instances[i], 100);
        printf("Total triplet numbers initially: %d.\n", countChoice(instances[i].feasibleChoices));
        if (instanceNoSolution(instances[i])) {
            printf("Instance no solution.\n\n");
            continue;
        }
        preprocessing(instances[i]);
            //printInstance(instances[i], 100);
        printf("Total triplet numbers after step 1: %d.\n", countChoice(instances[i].feasibleChoices));
        removeIPDominated(instances[i]);
            //printInstance(instances[i], 100);
        printf("Total triplet numbers after step 2: %d.\n", countChoice(instances[i].feasibleChoices));
        removeLPDominated(instances[i]);
            //printInstance(instances[i], 100);
        printf("Total triplet numbers after step 3: %d.\n\n", countChoice(instances[i].feasibleChoices));
    }
    return 0;
}