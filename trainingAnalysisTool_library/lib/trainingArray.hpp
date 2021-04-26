#ifndef TRAININGARRAY_HPP
#define TRAININGARRAY_HPP

#include "trainingInstance.hpp"
#include "running.hpp"

#include <vector>
#include <iostream>
#include <memory>
#include <map>

class TRAININGARRAY
{
    //(*this)[0]
    private:
        std::vector<std::shared_ptr<RUNNING>> m_trainingInstances;
    
    public:
    TRAININGARRAY()
    {
        std::cout << "In trainingArray" << std::endl;
    }

    //How to treat new training forms, create separate vector for each type(to access methods for sub classes) or have sub classes of TRAININGARRAY with those containers??
    void addRunningInstance(std::string type, int duration, double cadence, std::map<std::string, double> heartRateZones);

    double getAverageDuration();
    double getTotalDuration();
    double getAverageCadence();
    double getTotalCadence();
    int getNumberOfActivities();

    //Heart zone function, can I use input to not have to have 5 identical methods?
    double getTotalTimeSpentZone1();

    // Getters which uses date / week to decide what members in m_trainingInstances to use, for example
    double getWeeklyTimeSpentZone1(); //most likely some input to this function used to check corresponding member in RUNNING... will see
    std::vector<double> displayWeeklyTimeSpentZone1();

};
#endif