/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoverFabric.hpp
 * Author: Redbuzard
 *
 * Created on 25 novembre 2020, 17:23
 */

#ifndef MOVERFABRIC_HPP
#define MOVERFABRIC_HPP

#include "../movements/EntityMover.hpp"
#include <string>
#include <map>


class MoverFabric {
public:
    
//=================// Constructor //==================//
    
    /**
     * Default constructor
     */
    MoverFabric() = default;
    
    
//=================// Public methods //==================//
    
    /**
     * Creates an Entity mover from a string
     * @param str the string that will be analysed
     * @return a pointer to an EntityMover
     */
    EntityMover* createMover(const std::string& str) const;
    
    
private:
    
//=================// Private methods //==================//
    
    /**
     * Create a Continuous mover
     * @param params the parameters 
     * @return a pointer to an EntityMover
     */
    EntityMover* createContinuousMover(const std::string& params) const;
    
    /**
     * Create an empty mover
     * @return a pointer to an EntityMover
     */
    EntityMover* createNoMover() const;
    
    /**
     * Create a Random mover
     * @param params the parameters 
     * @return a pointer to an EntityMover
     */
    EntityMover* createRandomMover(const std::string& params) const;
    
    /**
     * Create a Rotationnal mover
     * @param params the parameters 
     * @return a pointer to an EntityMover
     */
    EntityMover* createRotationnalMover(const std::string& params) const;
    
    /**
     * Create a Sequence mover
     * @param params the parameters 
     * @return a pointer to an EntityMover
     */
    EntityMover* createSequenceMover(const std::string& params) const;
    
    
    /**
     * Get the MovementType corresponding to a string
     * @param str a const reference to the string
     * @return the MovementType corresponding
     */
    MovementType getMovement(const std::string& str) const;
    
    
//=================// Static Map //==================//
    
    // Map to confert string to MovementType
    static const std::map<std::string, MovementType> movementStrings;
};

#endif /* MOVERFABRIC_HPP */

