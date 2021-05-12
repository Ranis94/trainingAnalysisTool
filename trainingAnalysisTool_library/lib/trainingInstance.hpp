#ifndef TRAININGINSTANCE_HPP
#define TRAININGINSTANCE_HPP

#include <string>


/*
 * Refactor idea:
 *  Clean out base class, no less about derived classes -> use dynamic cast to find activity instead of getter functions
 *  Don't give type as input to TRAININGINstance, have m_type as defined enum of activites, then set m_type from derived classes based on dynamic casting or other method
*/

class TRAININGINSTANCE
{
    private:
        double m_duration;
        std::string m_type = ""; //Enum, then in getType() do dynamic casting to return correct type or not defined. Instanciate as "unclassified"
        int m_week;
        //Add date and time of training as well -> weekday and week number as well. For other purposes later
        // instead of boolean, use dynamic casting as "gating" 
        bool m_cadenceUsed{false}; // Set as false, changed to true from sub classes which has cadence as a value
        bool m_running{false}; // Set as false, changed to true from sub class RUNNING
        //add something to separate for cycling as well

    public:
        // week is only temporarily added
        TRAININGINSTANCE(std::string type, double duration, int week)
            : m_type{type}, m_duration{duration}, m_week{week}{}

        std::string getType(); // do dynamic casting to return correct type or not defined, change m_type
        double getDuration();
        int getWeek();
        bool getCadenceUsed();
        bool getRunningTrue(); //instead of bool, use enum and return training type

        // Might be unnecessary with setters, because after object is instanciated these should not change... I think
        virtual void setType(std::string type); //might change to protected instead....
        virtual void setDuration(double duration);
        //virtual void setWeek();// will in future take date as input and convert that to week

        // Method for sub classes to change m_cadenceUsed to true
        virtual void setCadenceUsedTrue();
        virtual void setRunningTrue();

        virtual double getCadence() = 0; //Makes class abstract, good since I never want to create TRAINININSTANCE object
        virtual double getZone(std::string zone) = 0;

};
#endif