#ifndef PROBABILITYVECTOR_H
#define PROBABILITYVECTOR_H

#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;
class ProbabilityVector
{
public:
    ProbabilityVector(int size);
    void addProbability(int amount);
    int getRandomResult();
private:
    int total, count, size;
    vector<int> probabilities;
};

#endif // PROBABILITYVECTOR_H
