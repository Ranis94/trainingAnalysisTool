#include "trainingArray.hpp"
#include <memory>

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
void TRAININGARRAY::displayZoneData(TypeEnum type)
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

        //Add function to convert TypeEnum to str
        std::cout << "#-------#" << std::endl;
        std::cout << "Week: " << week << ", total time "  << ": " << weeklyTime 
        << ", time in zone1: " << weeklyTimeInZones["zone1"] << "(" << percentageInZones["percentageZone1"] << "%)" 
        << ", time in zone2: " << weeklyTimeInZones["zone2"] << "(" << percentageInZones["percentageZone2"] << "%)" 
        << ", time in zone3: " << weeklyTimeInZones["zone3"] << "(" << percentageInZones["percentageZone3"] << "%)" 
        << ", time in zone4: " << weeklyTimeInZones["zone4"] << "(" << percentageInZones["percentageZone4"] << "%)" 
        << ", time in zone5: " << weeklyTimeInZones["zone5"] << "(" << percentageInZones["percentageZone5"] << "%)" << std::endl;
    }
}

/*
 * Method which get weekly time spent doing provided training type.  
 */
double TRAININGARRAY::getWeeklyTime(int week, TypeEnum type)
{
    double weeklyTime{0.0};
    auto filteredVec = createTypeAndWeekFilteredVec(week, type);

    auto weeklyTimeLambda = [&weeklyTime] (auto& elem) {weeklyTime += elem->getDuration();};
    std::for_each(filteredVec.begin(), filteredVec.end(), weeklyTimeLambda);

    return weeklyTime;
}

/*
 * Method to get weekly time in each heart rate zone doing provided training type.
 */
std::map<std::string, double> TRAININGARRAY::getWeeklyTimeSpentInZones(int week, TypeEnum type)
{
    double initVal{0.0};
    auto weeklyTimeSpentInZones = createZoneMap(initVal); //Why can addMaps() not be TRAININGARRAY:: but this not???
    auto filteredVec = createTypeAndWeekFilteredVec(week, type);

    auto weeklyHeartRateZoneLambda = [&weeklyTimeSpentInZones] (auto& elem) {
        std::shared_ptr<CARDIOTRAINING> elemP = std::dynamic_pointer_cast<CARDIOTRAINING>(elem);
        if(elemP != nullptr)
            addMaps(weeklyTimeSpentInZones, elemP->getHeartRateZones());
    };

    std::for_each(filteredVec.begin(), filteredVec.end(), weeklyHeartRateZoneLambda);

    return weeklyTimeSpentInZones;
}

/*
 * Method that finds percentage spent in each heart rate zone given weekly time spent in each heart rate zone and
 * total weekly time.
 * 
 * TODO: make this method smaller....
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
 * Method to display distance data for a given training type type on a weekly basis.
 * Method loops through from m_latestWeek to m_oldestWeek and finds weekly total distance doing provided training type.
 *
 * TODO: add optional argument to set how many weeks to display, by default loops all existing weeks
 * TODO: add loop / check for year as well
 * TODO: add check if increase is bigger than 10% in repect to previous week
 */
void TRAININGARRAY::displayDistanceData(TypeEnum type)
{
    int week;
    double oldDistance;
    double weeklyDistance;
    double percentageIncrease;

    for (week = m_latestWeek; week >= m_oldestWeek;  --week)
    {
        if(week >= m_oldestWeek + 1) //Maybe not good, might loose 1 week
        {
            oldDistance = getWeeklyDistance(week-1, type);
            weeklyDistance = getWeeklyDistance(week, type);
            percentageIncrease = getPercentualDistanceIncrease(weeklyDistance, oldDistance);

            //Write function that converts TypeEnum to std::string, add to cout
            std::cout << "#-------#" << std::endl;
            std::cout << "Week: " << week << ", total distance "  << ": " << weeklyDistance 
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
 * Method to get weekly distance doing provided training type.
 * Distance is a member of class CARDIOTRAINING, meaning 
 * lamda will do dynamic_pointer_cast<CARDIOTRAINING> and only 
 * access getDistance() if elemP != nullptr
 */
double TRAININGARRAY::getWeeklyDistance(int week, TypeEnum type)
{
    double weeklyDistance{0.0};
    auto filteredVec = createTypeAndWeekFilteredVec(week, type);

    auto weeklyDistanceLambda = [&weeklyDistance, week] (auto& elem) {
        std::shared_ptr<CARDIOTRAINING> elemP = std::dynamic_pointer_cast<CARDIOTRAINING>(elem);
        if(elemP != nullptr)
            weeklyDistance += elemP->getDistance();
    };

    std::for_each(filteredVec.begin(), filteredVec.end(), weeklyDistanceLambda);

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
 * Method that goes through m_trainingInstances and sorts out entries which fit
 * given week and type. 
 * 
 * Reason to not use lambda insted of standard for and if is that it did not work, 
 * assume issue arose since m_trainingInstances has shared_ptr entries
 */
std::vector<std::shared_ptr<TRAINING>> TRAININGARRAY::createTypeAndWeekFilteredVec(int week, TypeEnum type)
{
    std::vector<std::shared_ptr<TRAINING>> typeFilteredVec;

    for (auto &elem : m_trainingInstances)
    {
        if((elem->getType() == type) && (elem->getWeek() == week))
        {
            typeFilteredVec.push_back(elem);
        }
    }

    return typeFilteredVec;
}

/*
 * Method that creates a map for heart rate zones and sets value of all
 * keys to initVal
 */
 std::map<std::string, double> TRAININGARRAY::createZoneMap(double initVal)
 {
    std::map<std::string, double> weeklyTimeSpentInZones;
    weeklyTimeSpentInZones.insert(std::make_pair("zone1", initVal));
    weeklyTimeSpentInZones.insert(std::make_pair("zone2", initVal));
    weeklyTimeSpentInZones.insert(std::make_pair("zone3", initVal));
    weeklyTimeSpentInZones.insert(std::make_pair("zone4", initVal));
    weeklyTimeSpentInZones.insert(std::make_pair("zone5", initVal));

    return weeklyTimeSpentInZones;
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


// Working std::dynamic_pointer_cast
// auto checkRunningGetTimeLambda = [&weeklyTime, week] (auto& elem) {
//     //Working way using std::dynamic_pointer_cast
//     //std::shared_ptr<RUNNING> elemP = std::dynamic_pointer_cast<RUNNING>(elem);
//     //(elemP != nullptr)
//     if(elem->getWeek() == week){
//         weeklyTime += elem->getDuration();
//     }
// };

//
// auto createTypeFilterVecLambda = [type] (auto& elem) {
//     bool a = (elem->getType() != type);
//     return a;
// };

// std::remove_if(typeFilteredVec.begin(), typeFilteredVec.end(), createTypeFilterVecLambda);