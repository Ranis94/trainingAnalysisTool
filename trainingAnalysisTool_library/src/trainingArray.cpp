#include "trainingArray.hpp"

/*
 * Method to add a running instance to m_trainingInstances, calls method updateWeeks() in order to 
 * update m_latestWeek and m_oldestWeek according to content of vector
 */
void TRAININGARRAY::addRunningInstance(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones, double cadence)
{
    m_trainingInstances.push_back(std::make_shared<RUNNING>(duration, week, distance, pace,  heartRateZones, cadence));
    updateWeeks(week);
}

/*
 * Method to add a cycling instance to m_trainingInstances, calls method updateWeeks() in order to 
 * update m_latestWeek and m_oldestWeek according to content of vector
 */
void TRAININGARRAY::addCyclingInstance(double duration, int week, double distance, double pace, std::map<std::string, double> heartRateZones, double revolutionSpeed)
{
    m_trainingInstances.push_back(std::make_shared<CYCLING>(duration, week, distance, pace, heartRateZones, revolutionSpeed));
    updateWeeks(week);
}

/*
 * Method to update m_latestWeek and m_oldestWeek, assume activities are not stored incorrectly (week wise stored) 
 * and that latest week comes first in m_trainingInstances (push_back and read latest activities first)
 * 
 * TODO: Add year as well, since trainingInstances can be from different years as well....
 * TODO: Only works given all instances is from same year, will need to add more check for what year instance comes from later
 */
void TRAININGARRAY::updateWeeks(int week)
{
    if (m_trainingInstances.size() == 1)
    { 
        m_latestWeek = week;
        m_oldestWeek = week;
    }
    else
    {
        if (m_oldestWeek != week)
        {
            m_oldestWeek = week;
        }
    }
}

//---------------------display data and methods they use---------------------------

/*
 * Method to display hear rate zone data for a given training type type on a weekly basis.
 * Method loops through from m_latestWeek to m_oldestWeek and finds weekly total time and weekly 
 * time spent in each heart rate zones doing provided training type.
 *
 * TODO: add optional argument to set how many weeks to display, by default loops all existing weeks
 * TODO: add loop / check for year as well
 * TODO: ensure end output is printed in same size for each row
 * TODO: (?) Could add check on percentageInZones to see if zone4 and zone5 is > than 20%
 * TODO: (?) Add number of trainings of type for given week(pass by reference to getWeeklyTime() and change from std:for_each to numTrainigns = std::count_if )?
 */
void TRAININGARRAY::displayZoneData(std::string type)
{
    int week;
    double weeklyTime;
    std::map<std::string, double> weeklyTimeInZones;
    std::map<std::string, double> percentageInZones;

    for (week = m_latestWeek; week >= m_oldestWeek;  --week)
    {
        weeklyTime = getWeeklyTime(week, type);
        weeklyTimeInZones = getWeeklyTimeSpentInZones(week, type);
        percentageInZones = getPercentageSpentInZones(weeklyTimeInZones, weeklyTime);

        std::cout << "#-------#" << std::endl;
        std::cout << "Week: " << week << ", total time " << type << ": " << weeklyTime 
        << ", time in zone1: " << weeklyTimeInZones["zone1"] << "(" << percentageInZones["percentageZone1"] << "%)" 
        << ", time in zone2: " << weeklyTimeInZones["zone2"] << "(" << percentageInZones["percentageZone2"] << "%)" 
        << ", time in zone3: " << weeklyTimeInZones["zone3"] << "(" << percentageInZones["percentageZone3"] << "%)" 
        << ", time in zone4: " << weeklyTimeInZones["zone4"] << "(" << percentageInZones["percentageZone4"] << "%)" 
        << ", time in zone5: " << weeklyTimeInZones["zone5"] << "(" << percentageInZones["percentageZone5"] << "%)" << std::endl;
    }
}

/*
 * Method to display distance data for a given training type type on a weekly basis.
 * Method loops through from m_latestWeek to m_oldestWeek and finds weekly total distance doing provided training type.
 *
 * TODO: add optional argument to set how many weeks to display, by default loops all existing weeks
 * TODO: add loop / check for year as well
 * TODO: add check if increase is bigger than 10% in repect to previous week
 */
void TRAININGARRAY::displayDistanceData(std::string type)
{
    int week;
    double oldDistance;
    double weeklyDistance;
    double percentageIncrease;

    for (week = m_latestWeek; week >= m_oldestWeek;  --week)
    {
        if(week >= m_oldestWeek + 1)
        {
            oldDistance = getWeeklyDistance(week-1, type);
            weeklyDistance = getWeeklyDistance(week, type);
            percentageIncrease = getPercentualDistanceIncrease(weeklyDistance, oldDistance);

            std::cout << "#-------#" << std::endl;
            std::cout << "Week: " << week << ", total distance " << type << ": " << weeklyDistance 
            << ", increase: " << percentageIncrease << "%" << std::endl;
        }
        else
        {
            weeklyDistance = getWeeklyDistance(week, type);
            
            std::cout << "#-------#" << std::endl;
            std::cout << "Week: " << week << ", total distance " << type << ": " << weeklyDistance << std::endl;
        }
    }
}

/*
 * Method to get weekly time in each heart rate zone doing provided training type.
 *
 * TODO: Change getRunningTrue() to dynamic cast, if succeeded you know it's of correct type
 * TODO: Can getHeartRateZones() be used instead to decrease size of method?
 */
std::map<std::string, double> TRAININGARRAY::getWeeklyTimeSpentInZones(int week, std::string type)
{
    double initVal{0};
    std::map<std::string, double> weeklyTimeSpentInZones;
    weeklyTimeSpentInZones.insert(std::make_pair("zone1", initVal));
    weeklyTimeSpentInZones.insert(std::make_pair("zone2", initVal));
    weeklyTimeSpentInZones.insert(std::make_pair("zone3", initVal));
    weeklyTimeSpentInZones.insert(std::make_pair("zone4", initVal));
    weeklyTimeSpentInZones.insert(std::make_pair("zone5", initVal));

    if (type == "running")
    {
        auto checkRunningGetTimeInZoneLambda = [&weeklyTimeSpentInZones, week] (auto& elem) {
            if((elem->getRunningTrue() == true) && (elem->getWeek() == week)){
                addMaps(weeklyTimeSpentInZones, elem->getHeartRateZones());
            }
        };

        std::for_each(m_trainingInstances.begin(), m_trainingInstances.end(), checkRunningGetTimeInZoneLambda);
    }
    else
    {
        std::cout << "No matching types found" << std::endl;
    }

    return weeklyTimeSpentInZones;
}

/*
 * Method to get weekly time spent doing provided training type.  
 *
 * TODO: Change getRunningTrue() to dynamic cast, if succeeded you know it's of correct type
 * TODO: Add functionality for more training types than running
 * TODO: (?) Instead of switching over types here, creat void function which takes type, &weeklyTime, week and instance of run as input and call that function from std::for_each()
 */
double TRAININGARRAY::getWeeklyTime(int week, std::string type)
{
    double weeklyTime{0};

    if (type == "running")
    {
        auto checkRunningGetTimeLambda = [&weeklyTime, week] (auto& elem) {
            if((elem->getRunningTrue() == true) && (elem->getWeek() == week)){
                weeklyTime += elem->getDuration();
            }
        };

        std::for_each(m_trainingInstances.begin(), m_trainingInstances.end(), checkRunningGetTimeLambda);
    }
    else if (type == "cycling")
    {
        //TBA
    }
    else
    {
        std::cout << "No matching types found" << std::endl;
    }

    return weeklyTime;
}

/*
 * Method to get weekly distance doing provided training type.  
 *
 * TODO: Change getRunningTrue() to dynamic cast, if succeeded you know it's of correct type
 * TODO: Add functionality for more training types than running
 * TODO: (?) Instead of switching over types here, creat void function which takes type, &weeklyTime, week and instance of run as input and call that function from std::for_each()
 */
double TRAININGARRAY::getWeeklyDistance(int week, std::string type)
{
    double weeklyDistance{0};

    if (type == "running")
    {
        auto checkRunningGetDistanceLambda = [&weeklyDistance, week] (auto& elem) {
            if((elem->getRunningTrue() == true) && (elem->getWeek() == week)){
                weeklyDistance += elem->getDistance();
            }
        };

        std::for_each(m_trainingInstances.begin(), m_trainingInstances.end(), checkRunningGetDistanceLambda);
    }
    else if (type == "cycling")
    {
        //TBA
    }
    else
    {
        std::cout << "No matching types found" << std::endl;
    }

    return weeklyDistance;
}

/*
 * Method to get percentual increase between current distance and previous distance.
 * If previous distance is greater than current distance, return 0 % increase
 */
double TRAININGARRAY::getPercentualDistanceIncrease(double currentDistance, double previousDistance)
{
    double percentualIncrease{0};
    
    if (currentDistance >= previousDistance)
    {
        percentualIncrease = (currentDistance - previousDistance) / previousDistance * makePercentage;
    }
    
    return percentualIncrease;
}

/*
 * Method that finds percentage spent in each heart rate zone given weekly time spent in each heart rate zone and
 * total weekly time.
 */
std::map<std::string, double> TRAININGARRAY::getPercentageSpentInZones(std::map<std::string, double> WeeklyTimeSpentInZones, double weeklyTime)
{
    std::map<std::string, double> weeklyPercentageSpentInZones;

    double weeklyPercentageInZone1 = WeeklyTimeSpentInZones["zone1"] / weeklyTime * makePercentage;
    double weeklyPercentageInZone2 = WeeklyTimeSpentInZones["zone2"] / weeklyTime * makePercentage;
    double weeklyPercentageInZone3 = WeeklyTimeSpentInZones["zone3"] / weeklyTime * makePercentage;
    double weeklyPercentageInZone4 = WeeklyTimeSpentInZones["zone4"] / weeklyTime * makePercentage;
    double weeklyPercentageInZone5 = WeeklyTimeSpentInZones["zone5"] / weeklyTime * makePercentage;

    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone1", weeklyPercentageInZone1));
    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone2", weeklyPercentageInZone2));
    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone3", weeklyPercentageInZone3));
    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone4", weeklyPercentageInZone4));
    weeklyPercentageSpentInZones.insert(std::make_pair("percentageZone5", weeklyPercentageInZone5));

    return weeklyPercentageSpentInZones;
}

/*
 * Function that adds values from second std::map m2 to first std::map m1, assume
 * same size and keys in both maps
 */
void addMaps(std::map<std::string, double>& m1, std::map<std::string, double> m2)
{
    for(auto& x : m2)
        m1[x.first] += x.second;
}

//---------------------Are these even interesting??---------------------------

// double TRAININGARRAY::getTotalDuration()
// {
//     double totalDuration{0};

//     for(auto it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
//     {
//         totalDuration += (*it)->getDuration();
//     }

//     return totalDuration;
// }

// double TRAININGARRAY::getAverageDuration()
// {
//     double averageDuration{0};
    
//     averageDuration = getTotalDuration() / m_trainingInstances.size();

//     return averageDuration;
// }


// double TRAININGARRAY::getTotalCadence()
// {
//     double totalCadence{0};

//     for(auto it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
//     {
//         totalCadence += (*it)->getCadence();
//     }

//     return totalCadence;
// }

// double TRAININGARRAY::getAverageCadence()
// {
//     double averageCadence{0};
    
//     averageCadence = getTotalCadence() / getNumberOfActivitiesWithCadence();

//     return averageCadence;
// }

int TRAININGARRAY::getNumberOfActivities()
{
    return  m_trainingInstances.size();
}

// /*
// Method which returns number of activities in m_trainingInstances which uses cadence
// */
// int TRAININGARRAY::getNumberOfActivitiesWithCadence()
// {
//     auto checkCadenceLambda = [] (auto& elem)->bool {return (elem->getCadenceUsed() == true);};

//      int numberOfActivitiesWithCadence = std::count_if(m_trainingInstances.begin(), m_trainingInstances.end(), checkCadenceLambda);

//     return numberOfActivitiesWithCadence;
// }

// double TRAININGARRAY::getTotalTimeSpentZone(std::string zone)
// {
//     double totalTimeZone{0};

//     for(std::vector<std::shared_ptr<TRAINING>>::iterator it = m_trainingInstances.begin(); it != m_trainingInstances.end(); ++it)
//     {
//         totalTimeZone += (*it)->getZone(zone);
//     }

//     return totalTimeZone;
// }

int TRAININGARRAY::getLatestWeek()
{
    return m_latestWeek;
}

int TRAININGARRAY::getOldestWeek()
{
    return m_oldestWeek;
}