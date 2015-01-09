#ifndef PROBABILITYVECTOR_H
#define PROBABILITYVECTOR_H

#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
class ProbabilityVector
{
public:
    ProbabilityVector(int size);
    ProbabilityVector(vector<int> newVector);
    void addProbability(int amount);
    int getRandomResult();
    void printVector();
    int getProbability(int position);

    ProbabilityVector operator+(const ProbabilityVector &vector);

private:
    int total, count, size;
    vector<int> probabilities;
};

#endif // PROBABILITYVECTOR_H
