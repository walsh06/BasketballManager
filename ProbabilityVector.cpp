#include "ProbabilityVector.h"

ProbabilityVector::ProbabilityVector(int size)
{
    this->size = size;
    count = 0;
    total = 0;
}

ProbabilityVector::ProbabilityVector(vector<int> newVector)
{
    size = newVector.size();
    count = size;
    for(int i = 0; i < count; i++)
    {
        int amount = newVector[i];
        if(amount < 0)
        {
            amount = 0;
        }
        total += amount;
        probabilities.push_back(amount);
    }
}

void ProbabilityVector::addProbability(int amount)
{
    if(count < size)
    {
        if(amount < 0)
        {
            amount = 0;
        }
        total += amount;
        probabilities.push_back(amount);
        count++;
    }
}

int ProbabilityVector::getRandomResult()
{
    int randomNum = rand() % total, currentTotal = 0, result = -1;
    for(int i =0; i < count; i++)
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


int ProbabilityVector::getProbability(int position)
{
    return probabilities[position];
}

void ProbabilityVector::setProbability(int position, int value)
{
    probabilities[position] = value;
}

ProbabilityVector ProbabilityVector::operator+(const ProbabilityVector &vector)
{
    ProbabilityVector addedVector(this->size);
    if(this->count == vector.count)
    {
        for(int i = 0; i < count; i++)
        {
            addedVector.addProbability(this->probabilities[i] + vector.probabilities[i]);
        }
    }
    return addedVector;
}

void ProbabilityVector::printVector()
{
    for(int i =0; i < count; i++)
    {
        cout << probabilities[i] << " ";
    }
    cout << endl;
}
