#ifndef RUNNING_HPP
#define RUNNING_HPP

#include "cadenceExercise.hpp"

#include <string>
#include <map>

class RUNNING : public CADENCEEXERCISE
{
    public:
        RUNNING(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones, double cadence)
        : CADENCEEXERCISE(duration, week, distance, pace, heartRateZones, cadence){}
};

#endif