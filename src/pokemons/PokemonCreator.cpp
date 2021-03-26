#include "PokemonCreator.hpp"



Pokemon* createPokemon(PokemonID id, int level, int actualHealth){
    
    // Create the pokemon
    Pokemon* p = createPokemon(id, level);
    
    // Set the HP
    p->setHP(actualHealth);
    
    return p;
}



Pokemon* createPokemon(PokemonID id, int level, int actualHealth, PokemonMetadata metadata){
    
    // Create the pokemon
    Pokemon* p = createPokemon(id, level, actualHealth);
    
    // Set the HP
    p->setMetadata(metadata);
    
    return p;
}



Pokemon* createPokemon(PokemonID id, int level){
    return new Pokemon(id, level);
}