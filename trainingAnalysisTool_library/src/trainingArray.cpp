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


//---------------------display data and methods they use---------------------------

void TRAININGARRAY::displayZoneData(std::string type)
{
    int week;
    double weeklyTime;
    std::map<std::string, double> weeklyTimeInZones;
    std::map<std::string, double> percentageInZones;

    // For now this is enough, will need to add loop for year as well, just another for loop
    for (week = m_latestWeek; week >= m_oldestWeek;  --week)
    {
        weeklyTime = getWeeklyTime(week, type); // Get time spent for activity "type" during week "week"
        weeklyTimeInZones = getWeeklyTimeSpentInZones(week, type); // Get time spent in HR zones for activity "type" during week "week"
        percentageInZones = getPercentageSpentInZones(weeklyTimeInZones, weeklyTime);
        
        //Could add check on percentageInZones to see if zone4 and zone5 is > than 20%

        // Add number of trainings of type for given week(pass by reference to getWeeklyTime() and change from std:for_each to numTrainigns = std::count_if )?
        std::cout << "Week: " << week << ", total time " << type << ": " << weeklyTime << ", time in zone1: " << weeklyTimeInZones["zone1"] << "(" << percentageInZones["percentageZone1"] << "%)" <<std::endl;
    }
}

std::map<std::string, double> TRAININGARRAY::getPercentageSpentInZones(std::map<std::string, double> WeeklyTimeSpentInZones, double weeklyTime)
{
    std::map<std::string, double> weeklyPercentageSpentInZones;
    double weeklyPercentageInZone1 = WeeklyTimeSpentInZones["zone1"] / weeklyTime * 100;
    double weeklyPercentageInZone2 = WeeklyTimeSpentInZones["zone2"] / weeklyTime * 100;
    double weeklyPercentageInZone3 = WeeklyTimeSpentInZones["zone3"] / weeklyTime * 100;
    double weeklyPercentageInZone4 = WeeklyTimeSpentInZones["zone4"] / weeklyTime * 100;
    double weeklyPercentageInZone5 = WeeklyTimeSpentInZones["zone5"] / weeklyTime * 100;

    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone1", weeklyPercentageInZone1));
    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone2", weeklyPercentageInZone2));
    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone3", weeklyPercentageInZone3));
    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone4", weeklyPercentageInZone4));
    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone5", weeklyPercentageInZone5));

    return weeklyPercentageSpentInZones;
}

std::map<std::string, double> TRAININGARRAY::getWeeklyTimeSpentInZones(int week, std::string type)
{
    std::map<std::string, double> weeklyTimeSpentInZones;
    double weeklyTimeInZone1{0};
    double weeklyTimeInZone2{0};
    double weeklyTimeInZone3{0};
    double weeklyTimeInZone4{0};
    double weeklyTimeInZone5{0};

    //Switch case to create different lambdas for different types 
    if (type == "running")
    {
        //Change getRunningTrue() to dynamic cast, if succeeded you know it's of correct type
        //Can getHeartRateZones() be used instead??
        auto checkRunningGetTimeInZoneLambda = [&weeklyTimeInZone1, &weeklyTimeInZone2, &weeklyTimeInZone3, &weeklyTimeInZone4 , &weeklyTimeInZone5, week] (auto& elem) {
            if((elem->getRunningTrue() == true) && (elem->getWeek() == week)){
                weeklyTimeInZone1 += elem->getZone("zone1");
                weeklyTimeInZone2 += elem->getZone("zone2");
                weeklyTimeInZone3 += elem->getZone("zone3");
                weeklyTimeInZone4 += elem->getZone("zone4");
                weeklyTimeInZone5 += elem->getZone("zone5");
            }
        };

        std::for_each(m_trainingInstances.begin(), m_trainingInstances.end(), checkRunningGetTimeInZoneLambda);
    }
    else
    {
        std::cout << "No matching types found" << std::endl;
    }

    weeklyTimeSpentInZones.insert(std::make_pair("zone1", weeklyTimeInZone1));
    weeklyTimeSpentInZones.insert(std::make_pair("zone2", weeklyTimeInZone2));
    weeklyTimeSpentInZones.insert(std::make_pair("zone3", weeklyTimeInZone3));
    weeklyTimeSpentInZones.insert(std::make_pair("zone4", weeklyTimeInZone4));
    weeklyTimeSpentInZones.insert(std::make_pair("zone5", weeklyTimeInZone5));

    return weeklyTimeSpentInZones;
}

double TRAININGARRAY::getWeeklyTime(int week, std::string type)
{
    double weeklyTime{0};

    //Instead of  switching over types here, creat void function which takes type, &weeklyTime, week and instance of run as input and call that function from std::for_each()

    //Switch case to create different lambdas for different types 
    if (type == "running")
    {
        //(auto& elem) för performance, sen skulle jag nog skippa att "dereference" pekarna och köra med -> istället 
        //Change getRunningTrue() to dynamic cast, if succeeded you know it's of correct type
        auto checkRunningGetTimeLambda = [&weeklyTime, week] (auto& elem) {
            if((elem->getRunningTrue() == true) && (elem->getWeek() == week)){
                weeklyTime += elem->getDuration();
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




//---------------------Are these even interesting??---------------------------

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
    auto checkCadenceLambda = [] (auto& elem)->bool {return (elem->getCadenceUsed() == true);};

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