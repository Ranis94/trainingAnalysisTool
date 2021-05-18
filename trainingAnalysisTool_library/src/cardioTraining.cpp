#include "cardioTraining.hpp"

double CARDIOTRAINING::getDistance()
{
    return m_distance;
}

double CARDIOTRAINING::getPace()
{
    return m_pace;
}

double CARDIOTRAINING::getZone(std::string zone)
{
    // add check that zone exists
    return m_heartRateZones[zone];
}

std::map<std::string, double> CARDIOTRAINING::getHeartRateZones()
{
    return m_heartRateZones;
}