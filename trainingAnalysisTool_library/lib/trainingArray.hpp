#ifndef TRAININGARRAY_HPP
#define TRAININGARRAY_HPP

#include "trainingInstance.hpp"
#include "running.hpp"
#include "cycling.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include <map>

class TRAININGARRAY
{
    private:
        std::vector<std::shared_ptr<TRAININGINSTANCE>> m_trainingInstances;
        int m_latestWeek;
        int m_oldestWeek;

        void updateWeeks(int week);
    
    public:
    TRAININGARRAY()
    {
        std::cout << "In trainingArray" << std::endl;
    }

    void addRunningInstance(std::string type, double duration, int week, double cadence, std::map<std::string, double> heartRateZones);
    void addCyclingInstance(std::string type, double duration, int week, double revolutionSpeed);

    double getAverageDuration();
    double getTotalDuration();
    double getAverageCadence();
    double getTotalCadence();
    int getNumberOfActivitiesWithCadence();
    int getNumberOfActivities();

    int getLatestWeek();
    int getOldestWeek();

    double getTotalTimeSpentZone(std::string zone);

    // These methods should most likely be usefull to analyse my running
    std::map<std::string, double> getWeeklyTimeSpentInZones(int week, std::string type); //Get time spent in each zone for a GIVEN week and activity
    double getWeeklyTime(int week, std::string type); //Get total time for GIVEN week and activity
    void displayZoneData(std::string type); //Print out W# : Total time: # Zone1: #% ....  , add second input to decide how many weeks to show?

};
#endif