#include "ProbabilityVector.h"

/** ProbabilityVector Constructor with size parameter */
ProbabilityVector::ProbabilityVector(int size)
{
    this->size = size;
    count = 0;
    total = 0;
}

/** ProbabilityVector Constructor with vector parameter */
ProbabilityVector::ProbabilityVector(vector<int> newVector)
{
    //load the parameter vector into the object vector
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

/** Add a new probability to the vector */
void ProbabilityVector::addProbability(int amount)
{
    //if there is still space
    if(count < size)
    {
        if(amount < 0)
        {
            amount = 0;
        }
        //update totals
        total += amount;
        probabilities.push_back(amount);
        count++;
    }
}

/** Return a random result using weights */
int ProbabilityVector::getRandomResult()
{
    //generate a random between 0 and sum of all weights
    int randomNum = rand() % total, currentTotal = 0, result = -1;
    for(int i =0; i < count; i++)
    {
        //update the running total with each weight
        currentTotal += probabilities[i];
        //find the weight that is less than the random
        if(currentTotal > randomNum)
        {
            result = i;
            break;
        }
    }

    return result;
}

/** Return probability at position */
int ProbabilityVector::getProbability(int position)
{
    return probabilities[position];
}

/** Set the probability at position */
void ProbabilityVector::setProbability(int position, int value)
{
    probabilities[position] = value;
}

/** Overloaded plus operator */
ProbabilityVector ProbabilityVector::operator+(const ProbabilityVector &vector)
{
    ProbabilityVector addedVector(this->size);
    //check the sizes are the same of both vectors
    if(this->count == vector.count)
    {
        //loop through both vectors and add results
        for(int i = 0; i < count; i++)
        {
            addedVector.addProbability(this->probabilities[i] + vector.probabilities[i]);
        }
    }
    return addedVector;
}

/** Print the vector to console */
void ProbabilityVector::printVector()
{
    for(int i =0; i < count; i++)
    {
        cout << probabilities[i] << " ";
    }
    cout << endl;
}
