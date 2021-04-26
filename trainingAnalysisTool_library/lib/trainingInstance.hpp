#ifndef TRAININGINSTANCE_HPP
#define TRAININGINSTANCE_HPP

#include <string>

class TRAININGINSTANCE
{
    private:
        double m_duration;
        std::string m_type = "";
        //Add date and time of training as well -> weekday and week number as well. For other purposes later

    public:
        TRAININGINSTANCE(std::string type, double duration)
            : m_type{type}, m_duration{duration}{}

        std::string getType();
        double getDuration();

        // Might be unnecessary with setters, because after object is instanciated these should not change... I think
        virtual void setType(std::string type);
        virtual void setDuration(double duration);

};
#endif