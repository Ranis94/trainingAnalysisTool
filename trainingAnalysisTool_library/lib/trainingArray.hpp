#ifndef TRAININGARRAY_HPP
#define TRAININGARRAY_HPP

#include "trainingInstance.hpp"

#include <vector>
#include <iostream>

class TRAININGARRAY : public std::vector<TRAININGINSTANCE>
{
    //(*this)[0]
    public:

    TRAININGARRAY()
    {
        std::cout << "In trainingArray" << std::endl;
    }

    // Farsa struct
    double getAverageDuration();
    double getTotalDuration();

    // Running
    double getAverageCadence();
    double getTotalCadence();

};
#endif