#ifndef SWIMMING_HPP
#define SWIMMING_HPP

#include "strokeExercise.hpp"

#include <string>
#include <map>

class SWIMMING : public STROKEEXERCISE
{
    public:
        SWIMMING(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones, double strokeSpeed)
        : STROKEEXERCISE(duration, week, distance, pace, heartRateZones, strokeSpeed){}

};

#endif