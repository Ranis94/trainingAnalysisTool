#ifndef RUNNING_HPP
#define RUNNING_HPP

#include "trainingInstance.hpp"

#include <string>
#include <map>

class RUNNING : public TRAININGINSTANCE
{
    private:
        double m_cadance;
        bool cadenceUsed{true}; //class CYCLING bool cadenceUsed{false}; -> exist in base class, set in sub class
        std::map<std::string, double> m_heartRateZones; //Might not be private to RUNNING if I add more subclasses which uses heart rate zones

    public:
        RUNNING(std::string type, int duration, double cadence, std::map<std::string, double> heartRateZones)
            : TRAININGINSTANCE{type, duration}, m_cadance{cadence}, m_heartRateZones{heartRateZones}{} 

        double getCadence();

        //Is there really need for map and double getters...
        std::map<std::string, double> getHeartRateZones();
        double getZone(std::string zone);        

        // Might be unnecessary with setters, because after object is instanciated these should not change... I think
        void setCadence(double cadence);
        void setHeartRateZones(std::map<std::string, double> heartRateZones);
        
};
#endif