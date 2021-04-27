#include "trainingInstance.hpp"

// GETTERS
std::string TRAININGINSTANCE::getType()
{
    return m_type;
}

double TRAININGINSTANCE::getDuration()
{
    return m_duration;
}

// SETTERS
void TRAININGINSTANCE::setType(std::string type)
{
    m_type = type;
}

void TRAININGINSTANCE::setDuration(double duration)
{
    m_duration = duration;
}

void TRAININGINSTANCE::setCadenceUsedTrue()
{
    m_cadenceUsed = true;
}