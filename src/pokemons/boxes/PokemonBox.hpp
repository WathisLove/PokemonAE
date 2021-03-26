/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokemonBox.hpp
 * Author: Redbuzard
 *
 * Created on 29 décembre 2019, 21:16
 */

#ifndef POKEMONBOX_HPP
#define POKEMONBOX_HPP

#include <array>

#include "../Pokemon.hpp"


class PokemonBox {
public:
//==================// Constructor //=============//
    
    /**
     * Default contructor
     */
    PokemonBox();
    
    /**
     * Destructor
     */
    virtual ~PokemonBox();

    
//==================// Public methods //=============//
    
    /**
     * Check if there is some space in the box
     * @return true if there is some space left
     */
    bool hasPlace();
    
    
    /**
     * Adds a pokemon to the box
     * @warning throw an exception if the box is full
     * @param p a pointer to the added pokemon
     */
    void addPokemon(Pokemon* p);
    
    /**
     * Check if there is a pokemon at the given index
     * @param index the box index as an int
     * @return true if there is a pokemon at the given index
     */
    bool hasPokemonAtIndex(int index);
    
    /**
     * Adds a pokemon to the box at the given place
     * @warning throw an exception if the box is full
     * @param p a pointer to the added pokemon
     * @param index the box index as an int
     */
    void addPokemon(Pokemon* p, int index);
    
    
    /**
     * Remove the pokemon at the given index
     * @param index the box index as an int
     * @return a pointer to the pokemon
     */
    Pokemon* removePokemon(int index);
    
    
    /**
     * Check if the box is emtpy
     * @return true if the box is empty
     */
    bool isEmpty();
    
    
//==================// Getters / Setters //=============//
    
    
    /**
     * Get the pokemon at the given index
     * @param index the box index as an int
     * @return a pointer to the pokemon
     */
    Pokemon* getPokemonAt(int index);
    
    
    /**
     * Set the box name
     * @param name a const reference to the box name
     */
    void setName(const std::wstring& name);
    
    
    /**
     * Get the box name
     * @return a const reference to the box name
     */
    const std::wstring& getName();
    
    
    /**
     * Get next pokemon index
     * @param currentIndex the current index
     * @return the index of the next pokemon
     */
     int getNextPokemonIndex(int currentIndex);
     
    /**
     * Get previous pokemon index
     * @param currentIndex the current index
     * @return the index of the next pokemon
     */
     int getPreviousPokemonIndex(int currentIndex);
     
    
    
private:
//==================// Attributes //=============//
    
    // An array of 36 pokemons
    std::array<Pokemon*, 36> m_pokemons;
    
    // Box name
    std::wstring m_name;
};

#endif /* POKEMONBOX_HPP */

