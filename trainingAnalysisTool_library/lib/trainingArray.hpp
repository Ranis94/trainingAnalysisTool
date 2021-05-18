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

//TODO: Add method which finds (using dynamic casting) what traing type an instance is
//TODO: Add method which extract longest run each week and gives inc between weeks
//TODO: Separate methods and functions

//TODO: Should one instance of TRAININGARRAY only have one type of activity? IF SO, add m_type and then cast first added instance until a match is found. When
//adding nore instance, check before adding, that they are of same type?


class TRAININGARRAY
{
    private:
        std::vector<std::shared_ptr<TRAININGINSTANCE>> m_trainingInstances; //dynamic cast
        int m_latestWeek;
        int m_oldestWeek;
        int makePercentage{100};

        void updateWeeks(int week); //Private method to keep track of m_latestWeek and m_oldestWeek of activities in m_trainingInstances
    
    public:
    TRAININGARRAY()
    {
        std::cout << "In trainingArray" << std::endl;
    }

    //Adders
    void addRunningInstance(std::string type, double duration, double distance, int week, double cadence, std::map<std::string, double> heartRateZones);
    void addCyclingInstance(std::string type, double duration, double distance, int week, double revolutionSpeed);


    //Getters: specified by week and type
    std::map<std::string, double> getWeeklyTimeSpentInZones(int week, std::string type); //Get time spent in each zone for a given week and activity
    std::map<std::string, double> getPercentageSpentInZones(std::map<std::string, double> WeeklyTimeSpentInZones, double weeklyTime); //Get percentage spent in each zone
    double getWeeklyTime(int week, std::string type); //Get total time for given week and activity
    double getWeeklyDistance(int week, std::string type); //Get total distance for given week and activity
    double getPercentualDistanceIncrease(double currentDistance, double previousDistance);

    //Displayers
    void displayZoneData(std::string type);
    void displayDistanceData(std::string type);
    void displayCadenceData(std::string type); //TBA
    void displayNumberOfactivities(std::string type); //TBA


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
};
#endif