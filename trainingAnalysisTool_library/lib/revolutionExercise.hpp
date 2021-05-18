#ifndef REVOLUTIONEXERCISE_HPP
#define REVOLUTIONEXERCISE_HPP

#include "cardioTraining.hpp"

#include <string>
#include <map>

class REVOLUTIONEXERCISE : public CARDIOTRAINING
{
    private:
        double m_revolutionSpeed; // better name?

    public:
        REVOLUTIONEXERCISE(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones, double revolutionSpeed)
        : CARDIOTRAINING(duration, week, distance, pace, heartRateZones), m_revolutionSpeed{revolutionSpeed} {}

};

#endif