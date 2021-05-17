#ifndef CYCLING_HPP
#define CYCLING_HPP

//DUMMY CLASS TO TEST OTHER FUNTIONALITY

#include "trainingInstance.hpp"

#include <string>

class CYCLING : public TRAININGINSTANCE
{
    private:
        double m_revolutionSpeed;

    public:
        CYCLING(std::string type, double duration, double distance, int week, double revolutionSpeed)
            : TRAININGINSTANCE{type, duration, distance,week}, m_revolutionSpeed{revolutionSpeed}{}       

        //Deperate try to get code to compile
        double getCadence()
        {
            return 0;
        }
        double getZone(std::string zone)
        {
            return 0;
        } 
};
#endif