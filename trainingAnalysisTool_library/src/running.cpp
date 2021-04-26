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

double RUNNING::getZone1()
{
    return m_heartRateZones["zone1"];
}

double RUNNING::getZone2()
{
    return m_heartRateZones["zone2"];
}

double RUNNING::getZone3()
{
    return m_heartRateZones["zone3"];
}

double RUNNING::getZone4()
{
    return m_heartRateZones["zone4"];
}

double RUNNING::getZone5()
{
    return m_heartRateZones["zone5"];
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