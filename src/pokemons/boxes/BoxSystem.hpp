/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoxSystem.hpp
 * Author: Redbuzard
 *
 * Created on 30 décembre 2019, 21:57
 */

#ifndef BOXSYSTEM_HPP
#define BOXSYSTEM_HPP

#include "PokemonBox.hpp"
#include <vector>


class BoxSystem {
public:
//==================// Constructor / Destructor //=============//
    
    /**
     * Default constructor
     */
    BoxSystem();
    
    /**
     * Destructor
     */
    virtual ~BoxSystem();

//==================// Public methods //=============//

    /**
     * Adds a pokemon to the box system
     * @param pokemon a pointer to the pokemon
     */
    void addPokemon(Pokemon* pokemon);
    
    /**
     * Adds a pokemon to the box system
     * @param pokemon a pointer to the pokemon
     * @param boxNumber the number of the box
     * @param boxIndex the case in the box
     * @return the index of the box where the pokemon was placed
     */
    int addPokemon(Pokemon* pokemon, int boxNumber, int boxIndex);
    
    
//==================// Getters //=============//
    
    /**
     * Get the box of the given index
     * @param index the box index as an int
     * @return a pointer to the PokemonBox
     */
    PokemonBox* getBox(int index);
    
    
    /**
     * Get the BoxSystem size
     * @return the number of boxes as an int
     */
    int size();
    
    
//==================// Box methods //=============//
    
    /**
     * Adds a box to the box vector
     */
    void addEmptyBox();
    
    /**
     * Adds a box and a pokemon to the box system
     * @param pokemon a pointer to the pokemon added
     */
    void addBox(Pokemon* pokemon);
    
    
private:
    
//==================// Attributes //=============//
    
    // A vector of boxes
    std::vector<PokemonBox*> m_boxes;
};

#endif /* BOXSYSTEM_HPP */

