#ifndef CARDIOTRAINING_HPP
#define CARDIOTRAINING_HPP

#include "training.hpp"

#include <string>
#include <map>

class CARDIOTRAINING : public TRAINING
{
    private:
        double m_distance;
        double m_pace; //Should maybe use speed instead?
        std::map<std::string, double> m_heartRateZones;

    public:
        CARDIOTRAINING(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones)
        : TRAINING(duration, week), m_distance{distance}, m_pace{pace}, m_heartRateZones{heartRateZones} {}

    double getDistance();
    double getPace();
    double getZone(std::string zone); 
    std::map<std::string, double> getHeartRateZones();
};

#endif