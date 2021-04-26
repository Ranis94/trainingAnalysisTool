#include "trainingArray.hpp"

/*

*/
void TRAININGARRAY::addRunningInstance(std::string type, int duration, double cadence, std::map<std::string, double> heartRateZones)
{
    m_trainingInstances.push_back(std::make_shared<RUNNING>(type, duration, cadence, heartRateZones));
}


double TRAININGARRAY::getTotalDuration()
{
    double totalDuration{0};

    for(std::vector<std::shared_ptr<RUNNING>>::iterator it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
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

    for(std::vector<std::shared_ptr<RUNNING>>::iterator it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
    {
        totalCadence += (*it)->getCadence();
    }

    return totalCadence;
}

double TRAININGARRAY::getAverageCadence()
{
    double averageCadence{0};
    
    averageCadence = getTotalCadence() / m_trainingInstances.size();

    return averageCadence;
}

int TRAININGARRAY::getNumberOfActivities()
{
    return  m_trainingInstances.size();
}

double TRAININGARRAY::getTotalTimeSpentZone1()
{
    double totalTimeZone1{0};

    for(std::vector<std::shared_ptr<RUNNING>>::iterator it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
    {
        totalTimeZone1 += (*it)->getZone1();
    }

    return totalTimeZone1;
}