#include <algorithm>
#include "Pokedex.hpp"


Pokedex::Pokedex() {

}



void Pokedex::addPokemonSaw(PokemonID id) {
    // The number of time saw
    int saw = 0;
    
    // Get the number of time we saw the pokemon
    if(m_pokemonsSaw.find(id) != m_pokemonsSaw.end())
        saw = m_pokemonsSaw.at(id);
    
    
    // Increase it
    m_pokemonsSaw[id] = saw + 1;
}



void Pokedex::addPokemonCaptured(PokemonID id) {
    // The number of time saw
    int captured = 0;
    
    
    // Get the number of time we saw the pokemon
    if(m_pokemonsCaptured.find(id) != m_pokemonsCaptured.end())
        captured = m_pokemonsCaptured.at(id);
    
    
    // Increase it
    m_pokemonsCaptured[id] = captured + 1;
}



bool Pokedex::saw(PokemonID id) {
    // Try to find the ID in the set of pokemon Saw
    return m_pokemonsSaw.find(id) != m_pokemonsSaw.end();
}



bool Pokedex::captured(PokemonID id) {
    // Try to find the ID in the set of pokemon captured
    return m_pokemonsCaptured.find(id) != m_pokemonsCaptured.end();
}



int Pokedex::getNumberSaw(PokemonID id) {
    if(saw(id))
        return m_pokemonsSaw[id];
    else
        return 0;
}



int Pokedex::getNumberCaptured(PokemonID id) {
    if(captured(id))
        return m_pokemonsCaptured[id];
    else
        return 0;
}



int Pokedex::getTotalSaw() {
    int sum = 0;
    
    for(auto pair : m_pokemonsSaw){
        // Increase the sum
        sum += pair.second;
    }
    
    return sum;
}



int Pokedex::getTotalCaptured() {
    int sum = 0;
    
    for(auto pair : m_pokemonsCaptured){
        // Increase the sum
        sum += pair.second;
    }
    
    return sum;
}



const std::map<PokemonID, int>& Pokedex::getPokemonSaw() const {
    return m_pokemonsSaw;
}



const std::map<PokemonID, int>& Pokedex::getPokemonCaptured() const {
    return m_pokemonsCaptured;
}



std::vector<PokemonID>* Pokedex::getAllPokemons() const {
    // Create a set for all the pokemons
    std::vector<PokemonID>* set = new std::vector<PokemonID>();
    
    // Add each Pokemon to the set
    for(int id = (int)PokemonID::marcacrin; id < getPokedexSize(); id++){
        set->push_back((PokemonID)id);
    }
    
    
    return set;
}
