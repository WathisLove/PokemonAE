#include "../Item.hpp"

Item::EvBoost::EvBoost(int b, StatName s, BonusType bonus):
boost(b), stat(s), bonusType(bonus){
    
}


// Boost Stats
const std::multimap<ItemID, std::pair<StatName, float> > Item::statBoosters{
    
};



const std::multimap<ItemID, Item::PokemonStatBoost> Item::specialisedStatBoosters {
    
};



const std::multimap<ItemID, Item::EvBoost> Item::evBoosters {
    // Additive Bonuses
    {ItemID::poignPouv, Item::EvBoost(8, StatName::attack, BonusType::Additive)},
    {ItemID::ceintPouv, Item::EvBoost(8, StatName::defense, BonusType::Additive)},
    {ItemID::lentPouv, Item::EvBoost(8, StatName::special_attack, BonusType::Additive)},
    {ItemID::bandPouv, Item::EvBoost(8, StatName::special_defense, BonusType::Additive)},
    {ItemID::chainePouv, Item::EvBoost(8, StatName::speed, BonusType::Additive)},
    {ItemID::poidsPouv, Item::EvBoost(8, StatName::health, BonusType::Additive)},
            
    // Multiplicative Bonuses
    {ItemID::bracMacho, Item::EvBoost(2, StatName::attack, BonusType::Multiplicative)},
    {ItemID::bracMacho, Item::EvBoost(2, StatName::defense, BonusType::Multiplicative)},
    {ItemID::bracMacho, Item::EvBoost(2, StatName::special_attack, BonusType::Multiplicative)},
    {ItemID::bracMacho, Item::EvBoost(2, StatName::special_defense, BonusType::Multiplicative)},
    {ItemID::bracMacho, Item::EvBoost(2, StatName::speed, BonusType::Multiplicative)},
    {ItemID::bracMacho, Item::EvBoost(2, StatName::health, BonusType::Multiplicative)}
};



// Attack type boosters
const std::multimap<ItemID, std::pair<Type::TypeName, float> > Item::typeBoosters{
    {ItemID::crocDragon, {Type::Dragon, 1.2}},
    {ItemID::mouchSoie, {Type::Normal, 1.2}},
    {ItemID::encensMer, {Type::Water, 1.2}},
    {ItemID::encensFleur, {Type::Grass, 1.2}},
    {ItemID::grainMiracl, {Type::Grass, 1.2}},
    {ItemID::encensVague, {Type::Water, 1.2}},
    {ItemID::encensRoc, {Type::Rock, 1.2}},
    {ItemID::bizarEncens, {Type::Psychic, 1.2}},
    {ItemID::charbon, {Type::Fire, 1.2}},
    {ItemID::cuillertordu, {Type::Psychic, 1.2}},
    {ItemID::sableDoux, {Type::Ground, 1.2}},
    {ItemID::pierreDure, {Type::Rock, 1.2}},
    {ItemID::lunetNoires, {Type::Dark, 1.2}},
    {ItemID::poudreArg, {Type::Bug, 1.2}},
    {ItemID::ceintNoire, {Type::Fighting, 1.2}},
    {ItemID::aimant, {Type::Electric, 1.2}},
    {ItemID::eauMystique, {Type::Water, 1.2}},
    {ItemID::becPointu, {Type::Flying, 1.2}},
    {ItemID::peauMetal, {Type::Steel, 1.2}},
    {ItemID::picVenin, {Type::Poison, 1.2}},
    {ItemID::runeSort, {Type::Ghost, 1.2}},
    {ItemID::glaceEternel, {Type::Ice, 1.2}},
};



const std::multimap<ItemID, Item::PokemonTypeBoost> Item::specialisedTypeBoosters{
    
};



const std::map<ItemID, int> Item::critBooster{
    
};
    
    

// Heal 
const std::map<ItemID, int> Item::healHPs{
    {ItemID::potion, 20},
    {ItemID::superPotion, 50},
    {ItemID::hyperPotion, 200},
    {ItemID::eauFraiche, 30},
    {ItemID::sodaCool, 60},
    {ItemID::limonade, 80},
    {ItemID::laitMeumeu, 100},
    
    {ItemID::berrySitrus, 10},
};



const std::map<ItemID, float> Item::healPercentages{
    {ItemID::maxPotion, 100.},
    {ItemID::fullRestore, 100.},
    
    {ItemID::berrySitrus, 25.},
};



const std::map<ItemID, int> Item::ppRestored{
    {ItemID::huile, 10},
    {ItemID::huileMax, 1000},
    {ItemID::elixir, 10},
    {ItemID::maxElixir, 1000},
};



const std::map<ItemID, float> Item::revives{
    {ItemID::rappel, 50.},
    {ItemID::rappelMax, 100.},
};



const std::map<ItemID, MainStatusName> Item::statusHealed{
    {ItemID::antiBrule, MainStatusName::Burn},
    {ItemID::antiGel, MainStatusName::Freeze},
    {ItemID::antiPara, MainStatusName::Paralysis},
    {ItemID::antidote, MainStatusName::Poison},
    {ItemID::reveil, MainStatusName::Sleep},
            
    {ItemID::berryCeriz, MainStatusName::Paralysis},
    {ItemID::berryMaron, MainStatusName::Sleep},
    {ItemID::berryPecha, MainStatusName::Poison},
    {ItemID::berryFraive, MainStatusName::Burn},
    {ItemID::berryWillia, MainStatusName::Burn},
};



const std::set<ItemID> Item::allStatusHealed{
    ItemID::fullRestore,
    ItemID::totalSoin,
    ItemID::berryPrine
};



const std::set<ItemID> Item::confusionHealed = {
    ItemID::fullRestore,
    ItemID::totalSoin,
    
    ItemID::berryKika,
};



const std::map<ItemID, float> Item::xpBooster {
    {ItemID::oeufChance, 1.5},
};



const std::map<ItemID, float> Item::moneyBooster {
    {ItemID::pieceRune, 2.},
    {ItemID::encensVeine, 2.}
};



const std::map<ItemID, float> Item::happinessBooster{
    {ItemID::grelotZen, 2.}
};


const std::multimap<ItemID, std::pair<StatName, float> > Item::evoluBoosters{
    {ItemID::evoluRoc, {StatName::defense, 1.3}},
    {ItemID::evoluRoc, {StatName::special_defense, 1.3}},
};



const std::map<ItemID, float> Item::captureRates{
    {ItemID::pokeball, 1},
    {ItemID::superball, 1.5},
    {ItemID::hyperball, 2}
};



const std::multimap<ItemID, Item::StoneEvolution> Item::stoneEvolutions{
    
};