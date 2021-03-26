#include "PokemonID.hpp"
#include "../Utilities.hpp"

#include <map>
#include "../utility/Logger.hpp"

// Map for the string conversion
std::map<PokemonID, std::string> pokemonStrings{
    {PokemonID::UNKWNOWN, "UNK pkmn name"},
    {PokemonID::marcacrin, "marcacrin"},
    {PokemonID::cochignon, "cochignon"},
    {PokemonID::mammochon, "mammochon"},
    {PokemonID::pikachu, "pikachu"},
    {PokemonID::raichu, "raichu"},
    {PokemonID::etourmi, "etourmi"},
    {PokemonID::etourvol, "etourvol"},
    {PokemonID::etouraptor, "etouraptor"},
    {PokemonID::mystherbe, "mystherbe"},
    {PokemonID::galekid, "galekid"},
    {PokemonID::galegon, "galegon"},
    {PokemonID::galeking, "galeking"},
};



const std::string& pokemonIDtoString(PokemonID id){
    auto it = pokemonStrings.find(id);
    
    if(it != pokemonStrings.end())
        return it->second;
    else
        return pokemonStrings.at(PokemonID::UNKWNOWN);
}



PokemonID pokemonID(const std::string& str){
    // Check each string in the map
    for(auto it = pokemonStrings.begin(); it != pokemonStrings.end(); it++){
        // Check the current pair
        if(str == it->second)
            return it->first;
    }
    
    // Return a default ID and show a message
    Log("Couldn't find pokemon ID for " + str, Logger::FILE_ERROR);
    return PokemonID::pikachu;
}



int getPokedexSize(){
    return (int)PokemonID::galeking - (int)PokemonID::marcacrin + 1;
}



Stats* baseStatsOfID(PokemonID id){
    switch(id){
        case PokemonID::marcacrin : return new Stats(50, 50, 40, 30, 30, 50);
        case PokemonID::cochignon : return new Stats(100, 100, 80, 60, 60, 50);
        case PokemonID::mammochon : return new Stats(110, 130, 80, 70, 60, 80);
        case PokemonID::pikachu : return new Stats(35, 55, 40, 50, 50, 90);
        case PokemonID::raichu : return new Stats(60, 90, 55, 90, 80, 110);
        case PokemonID::etourmi : return new Stats(40, 55, 30, 30, 30, 60);
        case PokemonID::etourvol : return new Stats(55, 75, 50, 40, 40, 80);
        case PokemonID::etouraptor : return new Stats(85, 120, 70, 50, 60, 100);
        case PokemonID::mystherbe : return new Stats(45, 50, 55, 75, 65, 30);
        case PokemonID::galekid : return new Stats(50, 70, 100, 40, 40, 30);
        case PokemonID::galegon : return new Stats(60, 90, 140, 50, 50, 40);
        case PokemonID::galeking : return new Stats(70, 110, 180, 60, 60, 50);
        default : throw "Pokemon Stats unknown for ID " + toString(id);
    }
}



Stats* statsAtLevel(const Stats& baseStats, int level){
    int hp = (2*baseStats.getStatValue(StatName::health)*level)/100 +level+10;
    int atk = (2*baseStats.getStatValue(StatName::attack)*level)/100 +5;
    int def = (2*baseStats.getStatValue(StatName::defense)*level)/100 +5;
    int spa = (2*baseStats.getStatValue(StatName::special_attack)*level)/100 +5;
    int spd = (2*baseStats.getStatValue(StatName::special_defense)*level)/100 +5;
    int speed = (2*baseStats.getStatValue(StatName::speed)*level)/100 +5;
    return new Stats(hp, atk, def, spa, spd, speed);
}