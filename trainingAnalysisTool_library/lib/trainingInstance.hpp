#ifndef TRAININGINSTANCE_HPP
#define TRAININGINSTANCE_HPP

#include <string>
#include <map>

class TRAININGINSTANCE
{
    private:
        int m_duration;
        std::string m_type = "";
        //Add date and time of training as well -> weekday and week number as well. For other purposes later

    public:
        TRAININGINSTANCE(std::string type, int duration)
            : m_type{type}, m_duration{duration}{}

        std::string getType();
        int getDuration();
        virtual void setType(std::string type);
        virtual void setDuration(int duration);

};
#endif