#include "trainingInstance.hpp"

// GETTERS
std::string TRAININGINSTANCE::getType()
{
    return m_type;
}

int TRAININGINSTANCE::getDuration()
{
    return m_duration;
}

// SETTERS
void TRAININGINSTANCE::setType(std::string type)
{
    m_type = type;
}

void TRAININGINSTANCE::setDuration(int duration)
{
    m_duration = duration;
}