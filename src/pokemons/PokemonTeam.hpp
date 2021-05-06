/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokemonTeam.hpp
 * Author: Redbuzard
 *
 * Created on 21 juillet 2018, 12:26
 */

#ifndef POKEMONTEAM_HPP
#define POKEMONTEAM_HPP

#include <array>
#include <queue>

#include "Pokemon.hpp"


class PokemonTeam {
public:
//===================// Constructors //===================//
    
    PokemonTeam();
    
    virtual ~PokemonTeam();

    
//===================// Public functions //===================//
    
    /**
     * @return true if the array of Pokemon* is not full
     */
    bool canAddPokemon() const;
    
    /**
     * Add a pokemon to the array
     */
    void addPokemon(Pokemon* pkmn);
    
    /**
     * Remove the Pokemon at the given index
     * @warning the Pokemon is not deleted
     */
    Pokemon* removePokemonAt(int index);
    
    
    /**
     * Heal the whole pokemon team
     */
    void heal();
    
    
    /**
     * Switch the positions of two Pokemons
     * @param n1 the place of the first pokemon
     * @param n2 the place of the second pokemon
     */
    void switchPokemons(int n1, int n2);
    
    
    /**
     * Switch the positions of two Pokemons
     * @param p1 a pointer to the first pokemon
     * @param p2 a pointer to the second pokemon
     */
    void switchPokemons(Pokemon* p1, Pokemon* p2);
    
    
    /**
     * Save the order of the team in an other array
     */
    void saveTeamOrder();
    
    /**
     * Reload the order of the team from the other array
     */
    void reloadTeamOrder();
    
    
    /**
     * Check if all the pokemon are KOs
     * @return true if all the Pokemons are KO, false otherwise
     */
    bool areAllPokemonKOs();
    
    
    /**
     * Get the index of the first pokemon not KO
     * @return the index as an int
     */
    int getFirstNotKO();
    
    
    /**
     * Replace a pokemon in the team with an other
     * @param p a pointer to the new pokemon
     * @param index the index of the pokemon we are replacing
     * @return a pointer to the old pokemon at index
     */
    Pokemon* replacePokemonWith(Pokemon* p, int index);
    
    
    /**
     * Replace a pokemon in the team with an other
     * @param oldPoke a ponter to the old Pokemon
     * @param newPoke a pointer to the new Pokemon
     */
    void replacePokemonWith(Pokemon* oldPoke, Pokemon* newPoke);
    
    
    /**
     * Get the index of a pokemon in the team
     * @param p a pointer to the pokemon
     * @return the index of the pokemon in the team vector
     */
    int getIndexOf(Pokemon* p);
    
//===================// Getters / Setters //===================//
    
    /**
     * Returns a string that can be used to display infos about the pokemon
     * @return a const reference to a string
     */
    virtual std::string getInfoString() const;

    
    /**
     * @return a reference to the pokemon at the given index
     */
    Pokemon* getPokemonAt(int index);
    
    /**
     * @return the number of pokemon stored as an int
     */
    int getNbPokemon() const;
    
    
    /**
     * Get the number of pokemon not KO
     * @return the number of not KO as an int
     */
    int getNbNotKO() const;
    
    
    /**
     * Function called when the character leave the fight
     */
    void leaveFight();
    
    
    /**
     * Set the last pokemon that evolved in the team
     * @param p a pointer to the last pokemon that evolved
     */
    void addLeveledUp(Pokemon* p);
    
    /**
     * Get the last pokemon that evolved in the team
     * @return a pointer to the last pokemon that evolved
     */
    Pokemon* popLeveledUp();
    
    /**
     * Check if there are pokemon left that leveled up
     * @return true if the 
     */
    bool hasLeveledUpLeft() const;
    
    
private:
//===================// Attributes //===================//
    // Array of 6 pokemons
    std::array<Pokemon*, 6> m_pokemons;
    
    
    // Save of the Order
    std::array<Pokemon*, 6> m_pokemonsSaved;
    
    
    // Number of pokemon in the array
    int m_nbPokemons;
    
    // A queue of pointers to the last pokemons who evolved
    std::queue<Pokemon*> m_lastLeveledUp;
};

#endif /* POKEMONTEAM_HPP */

