#include "running.hpp"

// GETTERS
double RUNNING::getCadence()
{
    return m_cadance;
}

std::map<std::string, double> RUNNING::getHeartRateZones()
{
    return m_heartRateZones;
}

double RUNNING::getZone(std::string zone)
{
    // add check that zone exists
    return m_heartRateZones[zone];
}


// SETTERS
void RUNNING::setCadence(double cadence)
{
    m_cadance = cadence;
}

void RUNNING::setHeartRateZones(std::map<std::string, double> heartRateZones)
{
    m_heartRateZones = heartRateZones;
}