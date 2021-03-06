#ifndef CADENCEEXERCISE_HPP
#define CADENCEEXERCISE_HPP

#include "cardioTraining.hpp"

#include <string>
#include <map>

class CADENCEEXERCISE : public CARDIOTRAINING
{
    private:
        double m_cadence;

    public:
        CADENCEEXERCISE(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones, double cadence, TypeEnum type)
        : CARDIOTRAINING(duration, week, distance, pace, heartRateZones, type), m_cadence{cadence} {}

    double getCadence();
};

#endif