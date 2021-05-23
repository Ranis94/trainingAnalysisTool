#ifndef TRAINING_HPP
#define TRAINING_HPP

#include <string>
#include <map>

/*
 * TODO ideas:
 * Make all constructors/classes protected: such that only lowest classes in hierarchy and instanciate the constructors
 * create virtual TYPE collectdata() = 0; and implement in sub classes, use this in trainingArray instead of dynamic type casting. If that's possible?
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