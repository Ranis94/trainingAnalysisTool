#ifndef TRAININGINSTANCE_HPP
#define TRAININGINSTANCE_HPP

#include <string>

class TRAININGINSTANCE
{
    private:
        double m_duration;
        std::string m_type = "";
        //Add date and time of training as well -> weekday and week number as well. For other purposes later
        bool m_cadenceUsed{false}; // Set as false, changed to true from sub classes which has cadence as a value
        //add something to separate for cycling as well

    public:
        TRAININGINSTANCE(std::string type, double duration)
            : m_type{type}, m_duration{duration}{}

        std::string getType();
        double getDuration();
        bool getCadenceUsed();

        // Might be unnecessary with setters, because after object is instanciated these should not change... I think
        virtual void setType(std::string type); //might change to protected instead....
        virtual void setDuration(double duration);

        // Method for sub classes to change m_cadenceUsed to true
        virtual void setCadenceUsedTrue();

        virtual double getCadence() = 0; //Makes class abstract, good since I never want to create TRAINININSTANCE object
        virtual double getZone(std::string zone) = 0;

};
#endif