#ifndef TRAINING_HPP
#define TRAINING_HPP

#include <string>
#include <map>

/*
 * Refactor idea:
 *  Don't give type as input to TRAININGINstance, have m_type as defined enum of activites, then set m_type from derived classes based on dynamic casting or other method
*/

class TRAINING
{
    private:
        double m_duration;
        std::string m_type = ""; //Enum, then in getType() do dynamic casting to return correct type or not defined. Instanciate as "unclassified"
        int m_week; //Change to date when format is known
        //Add date and time of training as well -> weekday and week number as well. For other purposes later

    public:
        // week is only temporarily added
        TRAINING(double duration, int week)
            : m_duration{duration}, m_week{week}{}

        virtual ~TRAINING() //even virtual destructor makes a class polymorphic!
        {
            
        }
        
        void setType(); //TBA: Call from within constructor?
        std::string getType(); // do dynamic casting to return correct type or not defined, change m_type
        double getDuration();
        int getWeek();

        // void formatDate();// TBA:take date as input and convert that to week and year
};
#endif