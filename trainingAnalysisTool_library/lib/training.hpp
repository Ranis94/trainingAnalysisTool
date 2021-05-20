#ifndef TRAINING_HPP
#define TRAINING_HPP

#include <string>
#include <map>

/*
 * Refactor idea:
 * Add TypeEnum in all other child classes as well
 * Make all constructors/classes protected: such that only lowest classes in hierarchy and instanciate the constructors
 * Don't give type as input to TRAININGINstance, have m_type as defined enum of activites, then set m_type from derived classes based on dynamic casting or other method
*/

enum TypeEnum {unclassified = 0, running = 1, cycling = 2, swimming = 3}; //Add more types as it goes

class TRAINING
{
    private:
        double m_duration;
        TypeEnum m_typeEnum;
        int m_week; //Change to date when format is known
        //Add date and time of training as well -> weekday and week number as well. For other purposes later

    public:
        // week is only temporarily added
        TRAINING(double duration, int week, TypeEnum type = TypeEnum::unclassified)
            : m_duration{duration}, m_week{week}, m_typeEnum{type}{}

        virtual ~TRAINING(){} //Virtual destructor needed in a class polymorphic!
        
        TypeEnum getType();
        double getDuration();
        int getWeek();

        // void formatDate();// TBA:take date as input and convert that to week and year
};
#endif