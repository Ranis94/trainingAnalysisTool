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

int TRAININGINSTANCE::getWeek()
{
    return m_week;
}

bool TRAININGINSTANCE::getCadenceUsed()
{
    return m_cadenceUsed;
}

bool TRAININGINSTANCE::getRunningTrue()
{
    return m_running;
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

void TRAININGINSTANCE::setRunningTrue()
{
    m_running = true;
}