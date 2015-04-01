#ifndef PROBABILITYVECTOR_H
#define PROBABILITYVECTOR_H

#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>

/* Class used for calculating probabilities.
 * Takes in weights for probabilities and can return
 * a result. Also used for storing weights for later use
 * Provides an overloaded operator for easy combination of
 * vectors.
 */
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
    void setProbability(int position, int value);

    ProbabilityVector operator+(const ProbabilityVector &vector);

private:
    int total, count, size;
    vector<int> probabilities;
};

#endif // PROBABILITYVECTOR_H
