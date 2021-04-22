#include "trainingInstance.hpp"
#include "running.hpp"
#include "trainingArray.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

int main()
{
    // --- !=Run 1
    std::string notRun = "notRun";
    int durationNotRun = 30;
    TRAININGINSTANCE NotRun(notRun, durationNotRun);

    // --- Run 1
    std::string run1 = "run";
    int durationRun1 = 30;
    double cadanceRun1 = 170;
    std::map<std::string, double> heartZonesRun1;
    heartZonesRun1.insert(std::make_pair("zone1", 5));
    heartZonesRun1.insert(std::make_pair("zone2", 5));
    heartZonesRun1.insert(std::make_pair("zone3", 5));
    heartZonesRun1.insert(std::make_pair("zone4", 5));
    heartZonesRun1.insert(std::make_pair("zone5", 5));
    RUNNING Run1(run1, durationRun1, cadanceRun1, heartZonesRun1);

    // --- Run 2
    std::string run2 = "run";
    int durationRun2 = 36;
    double cadanceRun2 = 180;
    std::map<std::string, double> heartZonesRun2;
    heartZonesRun2.insert(std::make_pair("zone1", 6));
    heartZonesRun2.insert(std::make_pair("zone2", 6));
    heartZonesRun2.insert(std::make_pair("zone3", 6));
    heartZonesRun2.insert(std::make_pair("zone4", 6));
    heartZonesRun2.insert(std::make_pair("zone5", 6));
    RUNNING Run2(run2, durationRun2, cadanceRun2, heartZonesRun2);

    TRAININGARRAY onlyRunning;
    onlyRunning.push_back(Run1);
    onlyRunning.push_back(Run2);
    onlyRunning.push_back(NotRun);

    std::string testType = onlyRunning[0].getType();
    std::cout << testType << std::endl;
    std::cout << onlyRunning.size() << std::endl;

    // Test dur
    double avgDur = onlyRunning.getAverageDuration();
    std::cout << "avgDur: " << avgDur << std::endl;
    double totDur = onlyRunning.getTotalDuration();
    std::cout << "totDur: " << totDur << std::endl;
    // Test cadence
    double avgCad = onlyRunning.getAverageCadence();
    std::cout << "avgCad: " << avgCad << std::endl;
    double totCad = onlyRunning.getTotalCadence();
    std::cout << "totDur: " << totDur << std::endl;
}