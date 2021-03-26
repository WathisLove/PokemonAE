#include "PokemonBox.hpp"


PokemonBox::PokemonBox(){
    for(int i =0; i < m_pokemons.size(); i++){
        // Set all the pokemons to null
        m_pokemons.at(i) = nullptr;
    }
}



PokemonBox::~PokemonBox() {
    // Delete each pokemon from the memory
    for(Pokemon* p : m_pokemons)
        delete p;
}



bool PokemonBox::hasPlace() {
    // Check each box index
    for(int i =0; i < m_pokemons.size(); i++){
        // Set all the pokemons to null
        if(m_pokemons.at(i) == nullptr){
            return true;
        }
    }
    
    // No place was found
    return false;
}



bool PokemonBox::hasPokemonAtIndex(int index) {
    return m_pokemons.at(index) != nullptr;
}



void PokemonBox::addPokemon(Pokemon* p) {
    // Check each box index
    for(int i =0; i < m_pokemons.size(); i++){
        // Add the pokemon at the first null index
        if(m_pokemons.at(i) == nullptr){
            m_pokemons.at(i) = p;
            return;
        }
    }
    
    // If we didn't find a place
    throw std::string("There is no place left in the box !");
}



void PokemonBox::addPokemon(Pokemon* p, int index) {
    if(m_pokemons.at(index) == nullptr){
        m_pokemons.at(index) = p;
    }
    else{
        throw std::string("Can't add the pokemon at index " + toString(index));
    }
}



Pokemon* PokemonBox::removePokemon(int index) {
    Pokemon* poke = getPokemonAt(index);
    
    // Chekc if it is not null
    if(poke == nullptr)
        throw std::string("Removing null pokemon from the box");
    
    // Update the box
    m_pokemons.at(index) = nullptr;
    
    return poke;
}



bool PokemonBox::isEmpty() {

    for(int i =0; i < m_pokemons.size(); i++){
        // Check if there is a pokemon
        if(m_pokemons.at(i) != nullptr)
            return false;
    }
    
    // else there is no pokemon
    return true;
}



Pokemon* PokemonBox::getPokemonAt(int index) {
    return m_pokemons.at(index);
}



void PokemonBox::setName(const std::wstring& name) {
    m_name = name;
}



const std::wstring& PokemonBox::getName() {
    return m_name;
}



int PokemonBox::getNextPokemonIndex(int currentIndex) {
    // We look into the followin cases of the box
    for(int i = currentIndex+1; i < m_pokemons.size(); i++){
        if(hasPokemonAtIndex(i))
            return i;
    }
    
    // Else we start from 0
    for(int i = 0; i < m_pokemons.size(); i++){
        if(hasPokemonAtIndex(i))
            return i;
    }
    
    // Else we have an exception
    throw std::string("Can't find a next pokemon in the box");
}



int PokemonBox::getPreviousPokemonIndex(int currentIndex) {

    // We look into the previous cases of the box
    for(int i = currentIndex-1; i >= 0; i--){
        if(hasPokemonAtIndex(i))
            return i;
    }
    
    // Else we start from 0
    for(int i = m_pokemons.size()-1; i >= 0; i--){
        if(hasPokemonAtIndex(i))
            return i;
    }
    
    // Else we have an exception
    throw std::string("Can't find a previous pokemon in the box");
}
