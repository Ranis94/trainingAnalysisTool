#include "trainingArray.hpp"

/*

*/
void TRAININGARRAY::addRunningInstance(std::string type, double duration, int week, double cadence, std::map<std::string, double> heartRateZones)
{
    m_trainingInstances.push_back(std::make_shared<RUNNING>(type, duration, week, cadence, heartRateZones));
    updateWeeks(week);
}

void TRAININGARRAY::addCyclingInstance(std::string type, double duration, int week, double revolutionSpeed)
{
    m_trainingInstances.push_back(std::make_shared<CYCLING>(type, duration, week, revolutionSpeed));
    updateWeeks(week);
}

// Assume atctivities are not stored incorrectly (week wise) and that latest week comes first in m_trainingInstances (push_back and read latest activities first)
void TRAININGARRAY::updateWeeks(int week)
{
    if (m_trainingInstances.size() == 1)
    {
        //Later we will add year as well, since trainingInstances can be from different years as well....
        m_latestWeek = week;
        m_oldestWeek = week;
    }
    else
    {
        // Only works given all instances is from same year, will need to add more check for what year instance comes from later
        if (m_oldestWeek != week)
        {
            m_oldestWeek = week;
        }
    }

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

int TRAININGARRAY::getLatestWeek()
{
    return m_latestWeek;
}

int TRAININGARRAY::getOldestWeek()
{
    return m_oldestWeek;
}

void TRAININGARRAY::displayZoneData(std::string type)
{
    int week;
    double weeklyTime;
     std::map<std::string, double> weeklyTimeInZones;

    // For now this is enough, will need to add loop for year as well, just another for loop
    for (week = m_latestWeek; week >= m_oldestWeek;  --week)
    {
        std::cout << "week in loop: " << week << std::endl;
        weeklyTime = getWeeklyTime(week, type); // Get time spent for activity "type" during week "week"
        //weeklyTimeInZones = getWeeklyTimeSpentInZones(week, type); // Get time spent in HR zones for activity "type" during week "week"

        // Add printout W# : Total time: # Zone1: #% ....
        std::cout << "Week: " << week << ", total time: " << weeklyTime << std::endl;
    }
}

// std::map<std::string, double> TRAININGARRAY::getWeeklyTimeSpentInZones(int week, std::string type)
// {

// }

double TRAININGARRAY::getWeeklyTime(int week, std::string type)
{
    double weeklyTime{0};

    //Switch case to create different lambdas for different types 
    if (type == "running")
    {
        std::cout << "case running" << std::endl;
        auto checkRunningGetTimeLambda = [&weeklyTime, week] (auto elem) {
            if(((*elem).getRunningTrue() == true) && ((*elem).getWeek() == week)){
                weeklyTime += (*elem).getDuration();
            }
        };

        std::for_each(m_trainingInstances.begin(), m_trainingInstances.end(), checkRunningGetTimeLambda);
    }
    else
    {
        std::cout << "No matching types found" << std::endl;
    }

    return weeklyTime;
}