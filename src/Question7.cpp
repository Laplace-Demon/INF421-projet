#include <string>
#include <vector>
#include <utility>
#include <chrono>
#include <iostream>
#include <string>
#include <glpk.h>
#include <unistd.h>

#include "func.h"
#include "Question5.h"
#include "Question6.h"

using std :: vector;
using std :: chrono :: high_resolution_clock;
using std :: chrono :: duration_cast;
using std :: chrono :: microseconds;
using std :: cout;
using std :: endl;
using std :: to_string;
using std :: make_pair;

const size_t size = 4000005;
int *ia = new int[size];
int *ja = new int[size];
double *ar = new double[size];

glp_prob *prepareLPSolver(const Instance &instance) {
    glp_prob *lp;
    
    int N = instance.channelNumber, K = instance.userNumber, M = instance.choiceNumber, cnt = 0;
    
    lp = glp_create_prob();
    glp_set_prob_name(lp, "LP");
    glp_set_obj_dir(lp, GLP_MAX);
    glp_add_rows(lp, N + 1);
    glp_set_row_name(lp, 1, "dis");
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, (double)instance.totalEnergy);
    for (int i = 2; i <= N + 1; ++i) {
        glp_set_row_name(lp, i, &("s" + to_string(i))[0]);
        glp_set_row_bnds(lp, i, GLP_FX, 1.0, 1.0);
    }
    glp_add_cols(lp, N * K * M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            for (int k = 0; k < M; ++k) {
                glp_set_col_name(lp, 1 + k + j * M + i * K * M, &("x" + to_string(1 + k + j * M + i * K * M))[0]);
                glp_set_col_bnds(lp, 1 + k + j * M + i * K * M, GLP_DB, 0.0, 1.0);
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            for (int k = 0; k < M; ++k) {
                glp_set_obj_coef(lp, 1 + k + j * M + i * K * M, instance.rateMatrices[i][j][k]);
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            for (int k = 0; k < M; ++k) {
                ia[++cnt] = 1;
                ja[cnt] = 1 + k + j * M + i * K * M;
                ar[cnt] = (double)instance.powerMatrices[i][j][k];
            }
        }
    }
    for (int n = 0; n < N; ++n) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < K; ++j) {
                for (int k = 0; k < M; ++k) {
                    ia[++cnt] = n + 2;
                    ja[cnt] = 1 + k + j * M + i * K * M;
                    ar[cnt] = (i == n ? 1 : 0);
                }
            }
        }
    }
    glp_load_matrix(lp, cnt, ia, ja, ar);
    return lp;
}

int callLPSolver(glp_prob *lp) {
    return glp_simplex(lp, NULL);
}

LPSolverSolution parseSolverSolution(glp_prob *lp, Instance instance, int status) {
    LPSolverSolution solution;
    if (status != 0) return solution;
    solution.has_solution = true;
    int N = instance.channelNumber, K = instance.userNumber, M = instance.choiceNumber;
    bool is_integer = true;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            for (int k = 0; k < M; ++k) {
                double temp = glp_get_col_prim(lp, 1 + k + j * M + i * K * M);
                if (temp != 1.0 && temp != 0.0) is_integer = false;
                solution.solution.push_back(make_pair(glp_get_col_prim(lp, 1 + k + j * M + i * K * M), Choice(instance.powerMatrices[i][j][k], instance.rateMatrices[i][j][k], j)));
            }
        }
    }
    solution.is_integer = is_integer;
    return solution;
}

int main() {
    vector<Instance> instances = processInstances(5, false);
    int cnt = 1;
    for (Instance instance : instances) {
        printf("Instance %d:\n", cnt);

        printf("Greedy solution:\n");
        auto greedyStart = high_resolution_clock :: now();
        LPSolution greedySolution = greedySolveLP(instance);
        auto greedyStop = high_resolution_clock :: now();
        auto greedyDuration = duration_cast<microseconds>(greedyStop - greedyStart);
        LPSolutionAnalysis(instance, greedySolution);
        cout << "Time taken by function: " << greedyDuration.count() << " microseconds" << endl << endl;

        if (cnt == 4) {
            ++cnt;
            continue;
        }
        printf("LP solver:\n");
        glp_prob *lp = prepareLPSolver(instance);
        auto solverStart = high_resolution_clock :: now();
        int status = callLPSolver(lp);
        auto solverStop = high_resolution_clock :: now();
        auto solverDuration = duration_cast<microseconds>(solverStop - solverStart);
        LPSolverSolution solverSolution = parseSolverSolution(lp, instance, status);
        LPSolverSolutionAnalysis(instance, solverSolution);
        cout << "Time taken by function: " << solverDuration.count() << " microseconds" << endl << endl;

        ++cnt;
    }
    return 0;
}