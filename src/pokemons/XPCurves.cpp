#include <string>

#include "XPCurves.hpp"
#include "../Utilities.hpp"


int getXPToNextLevel(XPCurveType curveType, int currentLevel){
    
    // Check to have a correct level
    if(currentLevel <= 0 || currentLevel > 100){
        throw std::string("Incorrect level " + toString(currentLevel) + " for 'to levelXP' XP Curve");
    }
    
    if(currentLevel == 100)
        return 0;
    
    return getXPAtLevel(curveType, currentLevel+1) - getXPAtLevel(curveType, currentLevel);
}



int getXPAtLevel(XPCurveType curveType, int currentLevel){
    
    // Check to have a correct level
    if(currentLevel <= 0 || currentLevel > 100){
        throw std::string("Incorrect level " + toString(currentLevel) + " for 'at levelXP' Curve");
    }
    
    if(currentLevel == 1)
        return 0;
    
    if(curveType == XPCurveType::XP_Slow)
        return getSlowXPAtLevel(currentLevel);
    
    else if(curveType == XPCurveType::XP_Fast)
        return getFastXPAtLevel(currentLevel);
    
    else if(curveType == XPCurveType::XP_MediumSlow)
        return getMediumSlowXPAtLevel(currentLevel);
    
    else if(curveType == XPCurveType::XP_MediumFast)
        return getMediumFastXPAtLevel(currentLevel);
    
    else if(curveType == XPCurveType::XP_Erratic)
        return getErraticXPAtLevel(currentLevel);
    
    else if(curveType == XPCurveType::XP_Fluctuating)
        return getFluctuatingXPAtLevel(currentLevel);
}



int getSlowXPAtLevel(int currentLevel){
    
    
    return 1.25*(currentLevel*currentLevel*currentLevel);
}



int getFastXPAtLevel(int currentLevel){
    return 0.8*(currentLevel*currentLevel*currentLevel);
}



int getMediumSlowXPAtLevel(int currentLevel){
    
    int currentSquare = currentLevel*currentLevel;
    int currentCube = currentLevel*currentLevel*currentLevel;    
    
    return (1.2*currentCube-15.*currentSquare+100.*currentLevel-140.);
}



int getMediumFastXPAtLevel(int currentLevel){
    return currentLevel*currentLevel*currentLevel;
}



int getErraticXPAtLevel(int currentLevel){
    
    int currentCube = currentLevel*currentLevel*currentLevel;
    
    if(currentLevel <= 50){
        return currentCube*(100-currentLevel)/50;
    }
    else if(currentLevel <= 68){
        return currentCube*(150-currentLevel)/100;
    }
    else if(currentLevel <= 98){
        return currentCube*((int)(1911-10*currentLevel)/3)/500.;
    }
    else{
        return currentCube*(160-currentLevel)/100;
    }
}



int getFluctuatingXPAtLevel(int currentLevel){
    int currentCube = currentLevel*currentLevel*currentLevel;
    
    if(currentLevel <= 15){
        return currentCube*((currentLevel+1)/3 + 24)/50.;
    }
    else if(currentLevel <= 36){
        return currentCube*(currentLevel+14)/50.;
    }
    else{
        return currentCube*(currentLevel/2 + 32)/50.;
    }
}