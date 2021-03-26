/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XPCurves.hpp
 * Author: Redbuzard
 *
 * Created on 15 juillet 2019, 19:05
 */

#ifndef XPCURVES_HPP
#define XPCURVES_HPP

#include "../Enums.hpp"


/**
 * Get the xp needed to get to the next level (without taking in account the xp already gained)
 * @param curveType the type of the xp curve
 * @param currentLevel the current level of the pokemon
 * @return the number of xp points as an int
 */
int getXPToNextLevel(XPCurveType curveType, int currentLevel);



/**
 * Get the total xp of the pokmon at a given level
 * @param curveType the xp curve type of the Pokemon
 * @param currentLevel the current level of the pokemon
 * @return the total xp as an int
 */
int getXPAtLevel(XPCurveType curveType, int currentLevel);


/**
 * Get the total xp of the pokmon at a given level for the slow curve
 * @param currentLevel the current level of the pokemon
 * @return the total xp as an int
 */
int getSlowXPAtLevel(int currentLevel);


/**
 * Get the total xp of the pokmon at a given level for the fast curve
 * @param currentLevel the current level of the pokemon
 * @return the total xp as an int
 */
int getFastXPAtLevel(int currentLevel);


/**
 * Get the total xp of the pokmon at a given level for the medium slow curve
 * @param currentLevel the current level of the pokemon
 * @return the total xp as an int
 */
int getMediumSlowXPAtLevel(int currentLevel);


/**
 * Get the total xp of the pokmon at a given level for the medium fast curve
 * @param currentLevel the current level of the pokemon
 * @return the total xp as an int
 */
int getMediumFastXPAtLevel(int currentLevel);


/**
 * Get the total xp of the pokmon at a given level for the erratic curve
 * @param currentLevel the current level of the pokemon
 * @return the total xp as an int
 */
int getErraticXPAtLevel(int currentLevel);


/**
 * Get the total xp of the pokmon at a given level for the fluctuating curve
 * @param currentLevel the current level of the pokemon
 * @return the total xp as an int
 */
int getFluctuatingXPAtLevel(int currentLevel);


#endif /* XPCURVES_HPP */
