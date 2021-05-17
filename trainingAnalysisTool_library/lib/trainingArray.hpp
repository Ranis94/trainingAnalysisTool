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
        std::vector<std::shared_ptr<TRAININGINSTANCE>> m_trainingInstances; //dynamic cast
        int m_latestWeek;
        int m_oldestWeek;

        void updateWeeks(int week); //Private method to keep track of m_latestWeek and m_oldestWeek of activities in m_trainingInstances
    
    public:
    TRAININGARRAY()
    {
        std::cout << "In trainingArray" << std::endl;
    }

    //Adders
    void addRunningInstance(std::string type, double duration, int week, double cadence, std::map<std::string, double> heartRateZones);
    void addCyclingInstance(std::string type, double duration, int week, double revolutionSpeed);

    //Getters: general, as it is now not sure if any of these are really interesting...
    double getAverageDuration();
    double getTotalDuration();
    double getAverageCadence();
    double getTotalCadence();
    int getNumberOfActivities();
    int getLatestWeek();
    int getOldestWeek();
    double getTotalTimeSpentZone(std::string zone);
    int getNumberOfActivitiesWithCadence();

    //Getters: specified by week and type
    std::map<std::string, double> getWeeklyTimeSpentInZones(int week, std::string type); //Get time spent in each zone for a GIVEN week and activity
    std::map<std::string, double> getPercentageSpentInZones(std::map<std::string, double> WeeklyTimeSpentInZones, double weeklyTime); //Get percentage spent in each zone
    double getWeeklyTime(int week, std::string type); //Get total time for GIVEN week and activity

    //Displayers
    void displayZoneData(std::string type); //Print out W# : Total time: # Zone1: #% ....  , add second input to decide how many weeks to show?
    void displayDistanceData(std::string type); //TBA
    void displayCadenceData(std::string type); //TBA

};
#endif