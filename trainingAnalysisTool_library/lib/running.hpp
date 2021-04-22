#ifndef RUNNING_HPP
#define RUNNING_HPP

#include "trainingInstance.hpp"

#include <string>
#include <map>

class RUNNING : public TRAININGINSTANCE
{
    private:
        double m_cadance;
        std::map<std::string, double> m_heartRateZones;

    public:
        RUNNING(std::string type, int duration, double cadence, std::map<std::string, double> heartRateZones)
            : TRAININGINSTANCE{type, duration}, m_cadance{cadence}, m_heartRateZones{heartRateZones}{} 

        double getCadence();
        std::map<std::string, double> getHeartRateZones();

        // Might be unnecessary with setters, because after object is instanciated these should not change
        void setCadence(double cadence);
        void setHeartRateZones(std::map<std::string, double> heartRateZones);
        
};
#endif