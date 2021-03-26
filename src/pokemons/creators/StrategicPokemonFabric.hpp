/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrategicPokemonFabric.hpp
 * Author: Redbuzard
 *
 * Created on 24 septembre 2020, 16:56
 */

#ifndef STRATEGICPOKEMONFABRIC_HPP
#define STRATEGICPOKEMONFABRIC_HPP

#include <map>
#include "../Pokemon.hpp"
#include "../../Enums.hpp"

//===================// Enum //===================//
    
enum class StrategicPokemonID {
    MAMOSWINE_LIFE_ORB
};


    
/**
 * Utility class Used to instantiate Strategic pokemons
 * @warning is not designed to be instantiated
 */
class StrategicPokemonFabric {
public:
    
    
//===================// Public methods //===================//
    
    
    /**
     * Get the Strategic id for a given pokemon
     * @param str a const reference to the String
     * @return the pokemon Strategic ID
     */
    static StrategicPokemonID getStrategicID(const std::string& str);
    
    /**
     * Create a Strategic pokemon from a predefined set
     * @param id the StrategicID corresponding to the wanted set
     * @param level the target level of the strategic pokemon
     * @return a pointer to the pokemon created
     */
    static Pokemon* create(StrategicPokemonID id, unsigned int level);
    
private:
//===================// Map //===================//
    // Map for the strategic pokemon strings
    const static std::map<std::string, StrategicPokemonID> pokemonStratString;
    
    // Map for the pokemon IDs
    const static std::map<StrategicPokemonID, PokemonID> pokemonIDs;
    
    // Map for the Abilities
    const static std::map<StrategicPokemonID, AbilityID> abilityIDs;
    
    // Map for the Items
    const static std::map<StrategicPokemonID, ItemID> itemIDs;
    
    // Map for the Natures
    const static std::map<StrategicPokemonID, PokemonNature::NatureID> natureIDs;
    
    // Map for the EVs
    const static std::map<StrategicPokemonID, std::initializer_list<unsigned int>> evs;
    
    // Map for the Attacks (there must be at least 1 attack, and maximum 4 - it won't crash but won't be used )
    const static std::map<StrategicPokemonID, std::initializer_list<AttackID>> attackIDs;
    
    // Map for the pokemon roles
    const static std::map<StrategicPokemonID, StrategicRole> roles;
};

#endif /* STRATEGICPOKEMONFABRIC_HPP */

