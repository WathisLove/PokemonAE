#include "PokemonNature.hpp"
#include "./../Utilities.hpp"

// Tab for the Highered stats 
// (neutral natures have same values in both tabs)
const StatName PokemonNature::higheredTab [] = 
{
    attack, attack, attack, attack, attack, 
    defense, defense, defense, defense, defense,
    special_attack, special_attack, special_attack, special_attack, special_attack,
    special_defense, special_defense, special_defense, special_defense, special_defense,
    speed, speed, speed, speed, speed
};


// Tab for the Lowered stats 
const StatName PokemonNature::loweredTab [] =  
{
    attack, defense, special_attack, special_defense, speed,
    attack, defense, special_attack, special_defense, speed,
    attack, defense, special_attack, special_defense, speed,
    attack, defense, special_attack, special_defense, speed,
    attack, defense, special_attack, special_defense, speed
};



PokemonNature::PokemonNature() {
    // Generate a random Nature
    m_id = (NatureID)randomInt((int)Hardi, (int)Serieux);
}



PokemonNature::PokemonNature(NatureID id) :
m_id(id){

}



bool PokemonNature::isChangingStat() const{
    return getHigheredStat() != getLoweredStat();
}



StatName PokemonNature::getHigheredStat() const {
    return higheredTab[(int)m_id];
}



StatName PokemonNature::getLoweredStat() const {
    return loweredTab[(int)m_id];
}



std::string PokemonNature::saveAsString() {
    return toString(m_id);
}



std::wstring PokemonNature::toFormattedString() {
    return toFormattedString(m_id);
}



std::wstring PokemonNature::toFormattedString(NatureID id) {
    switch(id){
        case Hardi : return L"Hardi";
        case Solo : return L"Solo";
        case Rigide : return L"Rigide";
        case Mauvais : return L"Mauvais";
        case Brave : return L"Brave";
        case Assure : return L"Assuré";
        case Docile : return L"Docile";
        case Malin : return L"Malin";
        case Lache : return L"Lâche";
        case Relax : return L"Relax";
        case Modeste : return L"Modeste";
        case Doux : return L"Doux";
        case Pudique : return L"Pudique";
        case Foufou : return L"Foufou";
        case Discret : return L"Discret";
        case Calme : return L"Calme";
        case Gentil : return L"Gentil";
        case Prudent : return L"Prudent";
        case Bizarre : return L"Bizarre";
        case Malpoli : return L"Malpoli";
        case Timide : return L"Timide";
        case Presse : return L"Pressé";
        case Jovial : return L"Jovial";
        case Naif : return L"Naïf";
        case Serieux : return L"Sérieux";
        default:
            throw "Unknown Pokemon nature";
    }
}