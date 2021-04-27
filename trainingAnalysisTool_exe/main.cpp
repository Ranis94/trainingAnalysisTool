#include "trainingInstance.hpp"
#include "running.hpp"
#include "cycling.hpp"
#include "trainingArray.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

int main()
{

    // --- Run 1
    std::string run1 = "run";
    int durationRun1 = 30;
    double cadanceRun1 = 160;
    std::map<std::string, double> heartZonesRun1;
    heartZonesRun1.insert(std::make_pair("zone1", 5));
    heartZonesRun1.insert(std::make_pair("zone2", 5));
    heartZonesRun1.insert(std::make_pair("zone3", 5));
    heartZonesRun1.insert(std::make_pair("zone4", 5));
    heartZonesRun1.insert(std::make_pair("zone5", 5));

    // --- Run 2
    std::string run2 = "run";
    int durationRun2 = 40;
    double cadanceRun2 = 170;
    std::map<std::string, double> heartZonesRun2;
    heartZonesRun2.insert(std::make_pair("zone1", 10));
    heartZonesRun2.insert(std::make_pair("zone2", 10));
    heartZonesRun2.insert(std::make_pair("zone3", 10));
    heartZonesRun2.insert(std::make_pair("zone4", 10));
    heartZonesRun2.insert(std::make_pair("zone5", 10));

    // --- Run 3
    std::string run3 = "run";
    int durationRun3 = 50;
    double cadanceRun3 = 180;
    std::map<std::string, double> heartZonesRun3;
    heartZonesRun3.insert(std::make_pair("zone1", 20));
    heartZonesRun3.insert(std::make_pair("zone2", 20));
    heartZonesRun3.insert(std::make_pair("zone3", 20));
    heartZonesRun3.insert(std::make_pair("zone4", 20));
    heartZonesRun3.insert(std::make_pair("zone5", 20));

    // --- Cycling 1
    std::string cycling1 = "run";
    int durationCycling1 = 50;
    double revolutionSpeed1 = 180;

    // --- Cycling 2
    std::string cycling2 = "run";
    int durationCycling2 = 50;
    double revolutionSpeed2 = 180;

    std::cout << "map: " << heartZonesRun3["zone1"] << std::endl;

    TRAININGARRAY onlyRunning;
    onlyRunning.addRunningInstance(run1, durationRun1, cadanceRun1, heartZonesRun1);
    onlyRunning.addRunningInstance(run2, durationRun2, cadanceRun2, heartZonesRun2);
    onlyRunning.addRunningInstance(run3, durationRun3, cadanceRun3, heartZonesRun3);
    onlyRunning.addCyclingInstance(cycling1, durationCycling1, revolutionSpeed1);
    onlyRunning.addCyclingInstance(cycling2, durationCycling2, revolutionSpeed2);


    // Test dur
    std::cout << "avgDur: " << onlyRunning.getAverageDuration() << std::endl;
    std::cout << "totDur: " << onlyRunning.getTotalDuration() << std::endl;
    
    // Test cadence
    std::cout << "avgCad: " << onlyRunning.getAverageCadence() << std::endl;
    std::cout << "totDur: " << onlyRunning.getTotalCadence() << std::endl;

    // Test time in zone
    std::cout << "Time in Zone1: " << onlyRunning.getTotalTimeSpentZone("zone1") << std::endl;

    // Test number of activities
    std::cout << "Number of activities: " << onlyRunning.getNumberOfActivities() << std::endl;
    std::cout << "Number of activities with cadence: " << onlyRunning.getNumberOfActivitiesWithCadence() << std::endl;

}