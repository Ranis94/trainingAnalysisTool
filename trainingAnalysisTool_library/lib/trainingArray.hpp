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
    //(*this)[0]
    private:
        std::vector<std::shared_ptr<TRAININGINSTANCE>> m_trainingInstances;
    
    public:
    TRAININGARRAY()
    {
        std::cout << "In trainingArray" << std::endl;
    }

    //How to treat new training forms, create separate vector for each type(to access methods for sub classes) or have sub classes of TRAININGARRAY with those containers??
    void addRunningInstance(std::string type, double duration, double week, double cadence, std::map<std::string, double> heartRateZones);
    void addCyclingInstance(std::string type, double duration, double week, double revolutionSpeed);

    double getAverageDuration();
    double getTotalDuration();
    double getAverageCadence();
    double getTotalCadence();
    int getNumberOfActivitiesWithCadence();
    int getNumberOfActivities();

    double getTotalTimeSpentZone(std::string zone);

    // These methods should most likely be usefull to analyse my running
    std::map<std::string, double> getWeeklyTimeSpentInZones(double week, std::string type); //Get time spent in each zone for a GIVEN week and activity
    double getWeeklyTime(double week, std::string type); //Get total time for GIVEN week and activity
    void displayZoneData(std::string type); //Print out W# : Total time: # Zone1: #% ....

};
#endif