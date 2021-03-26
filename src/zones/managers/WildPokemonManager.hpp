/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WildPokemonManager.hpp
 * Author: Redbuzard
 *
 * Created on 21 décembre 2019, 13:15
 */

#ifndef WILDPOKEMONMANAGER_HPP
#define WILDPOKEMONMANAGER_HPP


#include <vector>
#include <map>

#include "../../pokemons/PokemonID.hpp"
#include "../../zones/ZoneID.hpp"
#include "../../pokemons/Pokemon.hpp"

class WildPokemonManager {
public:
    
//===============// Structs / Enums //===============//

    
    // Enum used to contain the encounter rarity
    enum EncounterRarity{
        Very_Common,
        Common,
        Uncommon,
        Rare,
        Very_Rare
    };
    
    // Struct containing the infos about a possible encounter
    struct PossibleEncounter{
        PokemonID id;
        int minLevel;
        int maxLevel;
        EncounterRarity rarity;
    };
    
//===============// Private Constructor //===============//
    
    WildPokemonManager();

    
//===============// Public methods //===============//
    
    /**
     * Check if the player encounters a pokemon
     * Updates the *lastEncounter* attribute if so
     * @param zone the current zone as a ZoneID
     * @return true if a pokemon appears
     */
    bool hasEncounteredPokemon(ZoneID zone);
    
    
    /**
     * Get the pokemon encountered
     * @return a pointer to the new pokemon
     */
    Pokemon* getEncounteredPokemon();
    
    
    /**
     * Get a vector containing all the pokemons that can be encountered in the given zone
     * @param zone the given zone as a ZoneID
     * @return a vector of PokemonID
     */
    std::vector<PokemonID> getPossiblePokemons(ZoneID zone);
    
    /**
     * Get a vector containing all the zones in which the given pokemon can be encountered
     * @param pokemonID the given pokemon as a pokemonID
     * @return a vector of ZoneID
     */
    std::vector<ZoneID> getPossibleZones(PokemonID pokemonID);
    
    
private:
    
//===============// Private static methods //===============//
    
    /**
     * Create a possible encounter
     * @param id the pokemon ID that can be encountered
     * @param rarity the encounter rarity
     * @param minLevel the minimum level at which the pokemon can be found
     * @param maxLevel the maximum level at which the pokemon can be found
     * @return the possible encounter as a struct
     */
    static PossibleEncounter createEncounter(PokemonID id, EncounterRarity rarity, int minLevel, int maxLevel);
    
    
    /**
     * Get the probability of the given encounter
     * @param rarity the encounter rarity
     * @return the probability as a float from 0 to 1
     */
    static float getEncounterProbability(EncounterRarity rarity);
    
    
    
//===============// Private methods //===============//
    
    /**
     * Add an encounter to the multimap
     * @param zone the ZoneID of the Zone
     * @param encounter the PossibleEncounter
     */
    void addEncounter(ZoneID zone, PossibleEncounter encounter);
    
    
    
    /**
     * Update the last encounter
     * @param encounter the new encounter
     */
    void updateLastEncounter(PossibleEncounter encounter);
    
    
//===============// Attributes //===============//
    
    // The last encounter
    PossibleEncounter m_lastEncounter;
    
    
    // The MultiMap of the encounters for each zone
    std::multimap<ZoneID, PossibleEncounter> m_possibleEncounters;
};

#endif /* WILDPOKEMONMANAGER_HPP */

