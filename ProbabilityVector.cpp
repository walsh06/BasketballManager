#include "ProbabilityVector.h"

ProbabilityVector::ProbabilityVector(int size)
{
    this->size = size;
    count = 0;
    total = 0;
}

void ProbabilityVector::addProbability(int amount)
{
    if(count < size)
    {
        total += amount;
        probabilities.push_back(amount);
        count++;
    }
}

int ProbabilityVector::getRandomResult()
{
    int randomNum = rand() % total, currentTotal = 0, result = -1;
    for(int i =0; i < size; i++)
    {
        currentTotal += probabilities[i];
        if(currentTotal > randomNum)
        {
            result = i;
            break;
        }
    }

    return result;
}
