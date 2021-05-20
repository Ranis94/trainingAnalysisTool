#ifndef CYCLING_HPP
#define CYCLING_HPP

#include "revolutionExercise.hpp"

#include <string>
#include <map>

class CYCLING : public REVOLUTIONEXERCISE
{
    public:
        CYCLING(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones, double revolutionSpeed)
        : REVOLUTIONEXERCISE(duration, week, distance, pace, heartRateZones, revolutionSpeed, TypeEnum::cycling){}

};

#endif