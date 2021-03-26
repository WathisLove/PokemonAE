#include "TrainerInfo.hpp"
#include "../Utilities.hpp"



const int TrainerInfo::nameSize = 2;

const std::wstring TrainerInfo::trainerNames [] = 
{
    L"Timothé",
    L"Jean-Jacques"
};



std::wstring TrainerInfo::getTrainerName(int trainerID) {
    // Look for a wrong trainer ID
    if(trainerID < 0 || trainerID >= nameSize)
        throw "Wrong trainer ID " + toString(trainerID) + " (size : " + toString(nameSize) + ")";
    
    // Else choose the name from the tab
    return trainerNames[trainerID];
}
