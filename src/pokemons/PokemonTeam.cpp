#include "PokemonTeam.hpp"
#include <string>
#include <iostream> 

PokemonTeam::PokemonTeam() :
m_nbPokemons(0){
    // Set all the pointers to null
    for(Pokemon* p : m_pokemons)
        p = nullptr;
    for(Pokemon* p : m_pokemonsSaved)
        p = nullptr;
}



PokemonTeam::~PokemonTeam() {
    for(int i = 0; i < m_nbPokemons; i++){
        delete m_pokemons.at(i);
    }
}



bool PokemonTeam::canAddPokemon() const {
    return m_nbPokemons < 6;
}



void PokemonTeam::addPokemon(Pokemon* pkmn) {
    if(m_nbPokemons == 6) throw std::string("Can't add a new pokemon : the team is full !");
    
    m_pokemons.at(m_nbPokemons) = pkmn;
    m_pokemonsSaved.at(m_nbPokemons) = pkmn;
    
    m_nbPokemons++;
}



int PokemonTeam::getNbPokemon() const {
    return m_nbPokemons;
}



int PokemonTeam::getNbNotKO() const {
    int sum(0);
    
    // Count the number of pokemons not KO
    for(int i = 0; i < m_nbPokemons; i++){
        if(!m_pokemons.at(i)->isKO())
            sum++;
    }
    
    return sum;
}



Pokemon* PokemonTeam::getPokemonAt(int index) {
    if(index >= m_nbPokemons) throw std::string("Can't get pokemon at the given index " + toString(index) + ": too large value");

    return m_pokemons.at(index);
}



Pokemon* PokemonTeam::removePokemonAt(int index) {
    if(index >= m_nbPokemons) throw std::string("Can't get pokemon at the given index : too large value");
    
    // Get the pokemon
    Pokemon* p = m_pokemons.at(index);
    
    // Reposition pokemon after the one deleted
    for(int i = index; i < m_nbPokemons-1; i++){
        m_pokemons.at(i) = m_pokemons.at(i+1);
    }
    // Set the old last one to null
    m_pokemons.at(m_nbPokemons-1) = nullptr;
    
    
    // Reduce the number of pokemon stored
    m_nbPokemons--;
    
    return p;
}



std::string PokemonTeam::getInfoString() const {
    std::string s("Nb pokemons : " + toString(m_nbPokemons) + "\n\n");
    
    for(int i = 0; i < m_nbPokemons; i++){
        s += m_pokemons.at(i)->getInfoString() + "\n\n";
    }
    
    return s;
}



void PokemonTeam::heal() {
    for(int i = 0; i < m_nbPokemons; i ++){
        m_pokemons.at(i)->healEverything();
    }
}



void PokemonTeam::leaveFight() {
    for(int i = 0; i < m_nbPokemons; i ++){
        m_pokemons.at(i)->leaveFight();
    }
}



void PokemonTeam::addLeveledUp(Pokemon* p) {
    m_lastLeveledUp.push(p);
}



Pokemon* PokemonTeam::popLeveledUp() {
    Pokemon* res = m_lastLeveledUp.front();
    m_lastLeveledUp.pop();
    return res;
}



bool PokemonTeam::hasLeveledUpLeft() const {
    return !m_lastLeveledUp.empty();
}



void PokemonTeam::switchPokemons(int n1, int n2) {
    if(n1 >= m_nbPokemons) throw std::string("Can't get pokemon at the given index : " + toString(n1));
    if(n2 >= m_nbPokemons) throw std::string("Can't get pokemon at the given index : " + toString(n2));
    
    std::cout << "P" << n1 << " " << m_pokemons.at(n1)->getName().toAnsiString() << " changed with " << "P" << n2 << " " << m_pokemons.at(n2)->getName().toAnsiString() << std::endl;
    
    // Switch the pokemons in the array
    Pokemon* p1 = m_pokemons.at(n1);
    Pokemon* p2 = m_pokemons.at(n2);
    
    m_pokemons[n1] = p2;
    m_pokemons[n2] = p1;
}



void PokemonTeam::switchPokemons(Pokemon* p1, Pokemon* p2){
    switchPokemons(getIndexOf(p1), getIndexOf(p2));
}


void PokemonTeam::reloadTeamOrder() {
    // Save each pokemon (even null pointers) from the main array to the second
    for(int i = 0; i < 6; i++){
        m_pokemons.at(i) = m_pokemonsSaved.at(i);
        
        m_pokemonsSaved.at(i) = m_pokemons.at(i);
    }
}



void PokemonTeam::saveTeamOrder() {
    // Load each pokemon (even null pointers) from the second array to the main
    for(int i = 0; i < 6; i++){
        m_pokemonsSaved.at(i) = m_pokemons.at(i);
    }
}



bool PokemonTeam::areAllPokemonKOs() {
    // Check each pokemon and if it is not KO return false
    for(int i = 0; i < m_nbPokemons; i++){
        if(!m_pokemons.at(i)->isKO()){
            return false;
        }
    }
    
    // Else return true
    return true;
}



int PokemonTeam::getFirstNotKO() {
    // Check each pokemon and if it is not KO return its index
    for(int i = 0; i < m_nbPokemons; i++){
        if(!m_pokemons.at(i)->isKO())
            return i;
    }
    
    // Else throw an exception
    throw std::string("All pokemons are KO in the Team !");
}



Pokemon* PokemonTeam::replacePokemonWith(Pokemon* p, int index) {
    // Get the old Poke
    Pokemon* oldPoke = m_pokemons.at(index);
    
    // Replace it with the new
    m_pokemons.at(index) = p;
    
    // Return the old poke
    return oldPoke;
}



Pokemon* PokemonTeam::replacePokemonWith(Pokemon* oldPoke, Pokemon* newPoke) {
    Pokemon* old = nullptr;
    
    // Replace in the team
    for(int i = 0; i < m_nbPokemons; i++){
        // Look if we found the old poke
        if(m_pokemons.at(i) == oldPoke){
            // Save it 
            old = m_pokemons.at(i);
            
            // And replace it
            m_pokemons.at(i) = newPoke;
            i = m_nbPokemons;
        }
    }
    
    // Replace in the Team order saved too
    for(int i = 0; i < m_nbPokemons; i++){
        // Look if we found the old poke
        if(m_pokemonsSaved.at(i) == oldPoke){
            m_pokemonsSaved.at(i) = newPoke;
            i = m_nbPokemons;
        }
    }
}



int PokemonTeam::getIndexOf(Pokemon* p) {
    // check each pokemon of the team
    for(int i = 0; i < m_nbPokemons; i++)
        if(m_pokemons.at(i) == p)
            return i;
    
    // Throw an exception if the pokemon was not found
    throw std::string("Can't find pokemon " + p->getName() + " in team");
}
