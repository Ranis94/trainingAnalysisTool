#include "trainingArray.hpp"

// Farsa struct
double TRAININGARRAY::getTotalDuration()
{
    double totalDuration{0};

    for(auto i = (*this).begin(); i != (*this).end(); i++ )
    {
        totalDuration += (*i).getDuration();
    }

    return totalDuration;
}

double TRAININGARRAY::getAverageDuration()
{
    double averageDuration{0};
    
    averageDuration = getTotalDuration() / (*this).size();

    return averageDuration;
}

// Running
double TRAININGARRAY::getTotalCadence()
{
    double totalCadence{0};

    for(auto i = (*this).begin(); i != (*this).end(); i++ )
    {
        totalCadence += (*i).getCadence();
    }

    return totalCadence;
}

double TRAININGARRAY::getAverageCadence()
{
    double averageCadence{0};
    
    averageCadence = getTotalCadence() / (*this).size();

    return averageCadence;
}