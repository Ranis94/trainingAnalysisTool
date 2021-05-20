#ifndef STROKEEXERCISE_HPP
#define STROKEEXERCISE_HPP

#include "cardioTraining.hpp"

#include <string>
#include <map>

class STROKEEXERCISE : public CARDIOTRAINING
{
    private:
        double m_strokeSpeed; //name?

    public:
        STROKEEXERCISE(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones, double strokeSpeed, TypeEnum type)
        : CARDIOTRAINING(duration, week, distance, pace, heartRateZones, type), m_strokeSpeed{strokeSpeed} {}

};

#endif