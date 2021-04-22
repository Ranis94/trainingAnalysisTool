#ifndef TRAININGARRAY_HPP
#define TRAININGARRAY_HPP

#include "trainingInstance.hpp"

#include <vector>
#include <iostream>

class TRAININGARRAY
{
    private:
        std::vector<std::shared_ptr<TRAININGINSTANCE>> m_trainingInstances;
    //(*this)[0]
    public:

    TRAININGARRAY()
    {
        std::cout << "In trainingArray" << std::endl;
    }

    void addTrainingInstance()
    {
        
    }

    // Farsa struct
    double getAverageDuration();
    double getTotalDuration();

    // Running
    double getAverageCadence();
    double getTotalCadence();

};
#endif