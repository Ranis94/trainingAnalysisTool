#include "trainingArray.hpp"

/*

*/
void TRAININGARRAY::addRunningInstance(std::string type, int duration, double cadence, std::map<std::string, double> heartRateZones)
{
    m_trainingInstances.push_back(std::make_shared<RUNNING>(type, duration, cadence, heartRateZones));
}

void TRAININGARRAY::addCyclingInstance(std::string type, int duration, double revolutionSpeed)
{
    m_trainingInstances.push_back(std::make_shared<CYCLING>(type, duration, revolutionSpeed));
}

double TRAININGARRAY::getTotalDuration()
{
    double totalDuration{0};

    for(auto it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
    {
        totalDuration += (*it)->getDuration();
    }

    return totalDuration;
}

double TRAININGARRAY::getAverageDuration()
{
    double averageDuration{0};
    
    averageDuration = getTotalDuration() / m_trainingInstances.size();

    return averageDuration;
}


double TRAININGARRAY::getTotalCadence()
{
    double totalCadence{0};

    for(auto it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
    {
        totalCadence += (*it)->getCadence();
    }

    return totalCadence;
}

double TRAININGARRAY::getAverageCadence()
{
    double averageCadence{0};
    
    averageCadence = getTotalCadence() / getNumberOfActivitiesWithCadence();
    //add method which finds number of entries with cadenceUsed == true -> use std count_if -> use lamda

    return averageCadence;
}

int TRAININGARRAY::getNumberOfActivities()
{
    return  m_trainingInstances.size();
}

/*
Method which returns number of activities in m_trainingInstances which uses cadence
*/
int TRAININGARRAY::getNumberOfActivitiesWithCadence()
{
    //[numberOfActivitiesWithCadence](int i){return i* % 2 == 0;}
    auto checkCadenceLambda = [] (auto elem)->bool {return ((*elem).getCadenceUsed() == true);};

    // pass index to lambda
     int numberOfActivitiesWithCadence = std::count_if(m_trainingInstances.begin(), m_trainingInstances.end(), checkCadenceLambda);

    return numberOfActivitiesWithCadence;
}

double TRAININGARRAY::getTotalTimeSpentZone(std::string zone)
{
    double totalTimeZone{0};

    for(std::vector<std::shared_ptr<TRAININGINSTANCE>>::iterator it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
    {
        totalTimeZone += (*it)->getZone(zone);
    }

    return totalTimeZone;
}