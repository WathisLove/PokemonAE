#include <map>
#include <cassert>

#include "AttackFabric.hpp"
#include "Attack.hpp"




// Map for the Attack names
std::map<AttackID, sf::String> AttackFabric::names = {
    {Charge, sf::String("Charge")},
    {BoueBombe, sf::String("Boue-Bombe")},
    {Eclair, sf::String("Eclair")},
    {ViveAttaque, sf::String("Vive-Attaque")},
    {EclatGlace, sf::String("Eclats-Glace")},
    {Seisme, sf::String("Séisme")},
    {Surpuissance, sf::String("Surpuissance")},
    {VitesseExtreme, sf::String("Vitesse Extrême")},
    {Avalanche, sf::String("Avalanche")},
    {DardVenin, sf::String("Dard-Venin")},
    {Poudreuse, sf::String("Poudreuse")},
    {Crochetvenin, sf::String("Crochetvenin")},
    {Flammeche, sf::String("Flammèche")},
    {Hypnose, sf::String("Hypnose")},
    {Rugissement, sf::String("Rugissement")},
    {Gonflette, sf::String("Gonflette")},
    {Lutte, sf::String("Lutte")},
    {DoublePied, sf::String("Double-Pied")},
    {ComboGriffe, sf::String("Combo-Griffe")},
    {Belier, sf::String("Belier")},
    {LanceSoleil, sf::String("Lance-Soleil")},
    {UltraLaser, sf::String("Ultra-Laser")},
    {PoingKarate, sf::String("Poing-Karate")},
    {Tunnelier, sf::String("Tunnelier")},
    {SouffleGlace, sf::String("Souffle-Glace")},
    {Abri, sf::String("Abri")},
};



std::map<AttackID, sf::String> AttackFabric::descriptions = {
    {Charge,  sf::String(L"L'attaque charge")},
    {BoueBombe,  sf::String(L"L'attaque boue-bombe")},
    {Eclair,  sf::String(L"L'attaque éclair")},
    {ViveAttaque,  sf::String(L"L'attaque vive-attaque")},
    {EclatGlace,  sf::String(L"L'attaque vive-attaque")},
    {Seisme,  sf::String(L"L'attaque vive-attaque")},
    {Surpuissance, sf::String(L"L'attaque Surpuissance")},
    {VitesseExtreme, sf::String(L"L'attaque Vitesse Extrême")},
    {Avalanche, sf::String(L"L'attaque Avalanche")},
    {DardVenin, sf::String(L"L'attaque Dard-Venin")},
    {Poudreuse, sf::String(L"L'attaque Poudreuse")},
    {Crochetvenin, sf::String(L"L'attaque Crochetvenin")},
    {Flammeche, sf::String(L"L'attaque Flammèche")},
    {Hypnose, sf::String(L"L'attaque Hypnose")},
    {Rugissement, sf::String(L"L'attaque Rugissement")},
    {Gonflette, sf::String(L"L'attaque Gonflette")},
    {Lutte, sf::String(L"L'attaque Lutte")},
    {DoublePied, sf::String(L"L'attaque Double-Pied")},
    {ComboGriffe, sf::String(L"L'attaque Combo-Griffe")},
    {Belier, sf::String(L"L'attaque Belier")},
    {LanceSoleil, sf::String(L"L'attaque Lance-Soleil")},
    {UltraLaser, sf::String(L"L'attaque Ultra-Laser")},
    {PoingKarate, sf::String(L"L'attaque Poing-Karate")},
    {Tunnelier, sf::String(L"L'attaque Tunnelier")},
    {SouffleGlace, sf::String(L"L'attaque Souffle-Glace")},
    {Abri, sf::String(L"L'attaque Abri")},
};

        
        
// Map for the Attack types
std::map<AttackID, Type> AttackFabric::types = {
    {Charge, Type(Type::Normal)},
    {BoueBombe, Type(Type::Ground)},
    {Eclair, Type(Type::Electric)},
    {ViveAttaque, Type(Type::Normal)},
    {EclatGlace, Type(Type::Ice)},
    {Seisme, Type(Type::Ground)},
    {Surpuissance, Type(Type::Fighting)},
    {VitesseExtreme, Type(Type::Normal)},
    {Avalanche, Type(Type::Ice)},
    {DardVenin, Type(Type::Poison)},
    {Poudreuse, Type(Type::Ice)},
    {Crochetvenin, Type(Type::Poison)},
    {Flammeche, Type(Type::Fire)},
    {Hypnose, Type(Type::Psychic)},
    {Rugissement, Type(Type::Normal)},
    {Gonflette, Type(Type::Fighting)},
    {Lutte, Type(Type::None)},
    {DoublePied, Type(Type::Fighting)},
    {ComboGriffe, Type(Type::Normal)},
    {Belier, Type(Type::Normal)},
    {Belier, Type(Type::Normal)},
    {LanceSoleil, Type(Type::Grass)},
    {UltraLaser, Type(Type::Normal)},
    {PoingKarate, Type(Type::Fighting)},
    {Tunnelier, Type(Type::Ground)},
    {SouffleGlace, Type(Type::Ice)},
    {Abri, Type(Type::Normal)},
};



// Map for the Attack categories
std::map<AttackID, Attack::AttackCategory> AttackFabric::categories = {
    {Charge, Attack::Physical},
    {BoueBombe, Attack::Special},
    {Eclair, Attack::Special},
    {ViveAttaque, Attack::Physical},
    {EclatGlace, Attack::Physical},
    {Seisme, Attack::Physical},
    {Surpuissance, Attack::Physical},
    {VitesseExtreme, Attack::Physical},
    {Avalanche, Attack::Physical},
    {DardVenin, Attack::Physical},
    {Poudreuse, Attack::Special},
    {Crochetvenin, Attack::Physical},
    {Flammeche, Attack::Special},
    {Hypnose, Attack::Special},
    {Rugissement, Attack::Status},
    {Gonflette, Attack::Status},
    {Lutte, Attack::Physical},
    {DoublePied, Attack::Physical},
    {ComboGriffe, Attack::Physical},
    {Belier, Attack::Physical},
    {LanceSoleil, Attack::Special},
    {UltraLaser, Attack::Special},
    {PoingKarate, Attack::Physical},
    {Tunnelier, Attack::Physical},
    {SouffleGlace, Attack::Special},
    {Abri, Attack::Status},
};



// Map for the Targets
std::map<AttackID, Attack::AttackTarget> AttackFabric::targets = {
    {Charge, Attack::SingleEnnemy},
    {BoueBombe, Attack::SingleEnnemy},
    {Eclair, Attack::SingleEnnemy},
    {ViveAttaque, Attack::SingleEnnemy},
    {EclatGlace, Attack::SingleEnnemy},
    {Seisme, Attack::AllPokemons},
    {Surpuissance, Attack::SingleEnnemy},
    {VitesseExtreme, Attack::SingleEnnemy},
    {Avalanche, Attack::SingleEnnemy},
    {DardVenin, Attack::SingleEnnemy},
    {Poudreuse, Attack::AllEnnemies},
    {Crochetvenin, Attack::SingleEnnemy},
    {Flammeche, Attack::SingleEnnemy},
    {Hypnose, Attack::SingleEnnemy},
    {Rugissement, Attack::AllEnnemies},
    {Gonflette, Attack::Self},
    {Lutte, Attack::SingleEnnemy},
    {DoublePied, Attack::SingleEnnemy},
    {ComboGriffe, Attack::SingleEnnemy},
    {Belier, Attack::SingleEnnemy},
    {LanceSoleil, Attack::SingleEnnemy},
    {UltraLaser, Attack::SingleEnnemy},
    {PoingKarate, Attack::SingleEnnemy},
    {Tunnelier, Attack::SingleEnnemy},
    {SouffleGlace, Attack::SingleEnnemy},
    {Abri, Attack::Self},
};



// Map for the damages
std::map<AttackID, int> AttackFabric::damages = {
    {Charge, 40},
    {BoueBombe, 65},
    {Eclair, 40},
    {ViveAttaque, 40},
    {EclatGlace, 40},
    {Seisme, 100},
    {Surpuissance, 120},
    {VitesseExtreme, 80},
    {Avalanche, 60},
    {DardVenin, 15},
    {Poudreuse, 40},
    {Crochetvenin, 50},
    {Flammeche, 40},
    {Lutte, 50},
    {DoublePied, 30},
    {ComboGriffe, 18},
    {Belier, 90},
    {LanceSoleil, 120},
    {UltraLaser, 150},
    {PoingKarate, 50},
    {Tunnelier, 80},
    {SouffleGlace, 60},
};



// Map for the precision
std::map<AttackID, int> AttackFabric::accuracies = {
    {BoueBombe, 85},
    {Hypnose, 60},
    {ComboGriffe, 80},
    {Belier, 85},
    {UltraLaser, 90},
    {Tunnelier, 95},
    {SouffleGlace, 90},
};



// Map for the precision
std::map<AttackID, int> AttackFabric::ppMax = {
    {Charge, 35},
    {BoueBombe, 10},
    {Eclair, 30},
    {ViveAttaque, 30},
    {EclatGlace, 30},
    {Seisme, 10},
    {Surpuissance, 5},
    {VitesseExtreme, 5},
    {Avalanche, 10},
    {DardVenin, 35},
    {Poudreuse, 25},
    {Crochetvenin, 15},
    {Flammeche, 25},
    {Hypnose, 20},
    {Rugissement, 20},
    {Gonflette, 20},
    {Lutte, 50},
    {DoublePied, 30},
    {Belier, 20},
    {LanceSoleil, 10},
    {UltraLaser, 5},
    {PoingKarate, 25},
    {Tunnelier, 10},
    {SouffleGlace, 10},
};



// Map for the MainStatus
std::map<AttackID, AttackFabric::PossibleStatus> AttackFabric::mainStatuses = {
    {Eclair, {MainStatusName::Paralysis, 0.1}},
    {DardVenin, {MainStatusName::Poison, 0.3}},
    {Poudreuse, {MainStatusName::Freeze, 0.1}},
    {Crochetvenin, {MainStatusName::Poison, 0.5}},
    {Flammeche, {MainStatusName::Burn, 0.1}},
    {Hypnose, {MainStatusName::Sleep, 1}},
};



// Map for the priorities
std::map<AttackID, int> AttackFabric::priorities = {
    {ViveAttaque, 1},
    {EclatGlace, 1},
    {VitesseExtreme, 2},
    {Avalanche, -4},
    {Abri, 4},
};



// Map for the critical levels
std::map<AttackID, int> AttackFabric::critLevels = {
    {PoingKarate, 2},
    {Tunnelier, 2},
};



// Set for the Attack that double damages when hit before
std::map<AttackID, StatsChanger> AttackFabric::statsChangers = {
    {Surpuissance, StatsChanger(Team::allied, -1, -1, 0, 0, 0, 0, 0)},
    {Rugissement, StatsChanger(Team::ennemy, -1, 0, 0, 0, 0, 0, 0)},
    {Gonflette, StatsChanger(Team::allied, 1, 1, 0, 0, 0, 0, 0)},
};



// Map for the hits
std::map<AttackID, std::array<int, 2>>AttackFabric:: AttackFabric::hits = {
    {DoublePied, {2, 2}},
    {ComboGriffe, {2, 5}},
};



// Map for the recoils percentages
std::map<AttackID, int> AttackFabric::recoils = {
    {Lutte, 25},
    {Belier, 25},
};



// Maps for the breaks
std::set<AttackID> AttackFabric::breakBefore = {
    LanceSoleil,
};


std::set<AttackID> AttackFabric::breakAfter = {
    UltraLaser
};




// Set for the Attack that double damages when hit before
std::set<AttackID> AttackFabric::doubleDamage = {
    Avalanche,
};



// Map for the always critical attacks
std::set<AttackID> AttackFabric::alwaysCriticals = {
    SouffleGlace,
};



// Map for the always critical attacks
std::set<AttackID> AttackFabric::protects = {
    Abri
};





Attack* AttackFabric::createAttack(AttackID id) {
    // Get the Attack name, type, category and target
    auto nameIt = names.find(id);
    auto typeIt = types.find(id);
    auto categoryIt = categories.find(id);
    auto targetIt = targets.find(id);
    auto descriptionIt = descriptions.find(id);
    
    // Assert all of theme are present in the map
    assert(nameIt != names.end() && typeIt != types.end() && categoryIt != categories.end() && targetIt != targets.end() && descriptionIt != descriptions.end());
    
    
    // Create the Attack
    Attack* atk = new Attack(id, nameIt->second, typeIt->second, categoryIt->second, targetIt->second, descriptionIt->second);
    
    
    //==========// Attributes //==========//
    
    // Damage
    auto damageIt = damages.find(id);
    if(damageIt != damages.end()) atk->setDamage(damageIt->second);
    
    // Accuracy
    auto accuracyIt = accuracies.find(id);
    if(accuracyIt != accuracies.end()) atk->setAccuracy(accuracyIt->second);
    
    // PP Max
    auto ppMaxIt = ppMax.find(id);
    if(ppMaxIt != ppMax.end()) atk->setPPMax(ppMaxIt->second);
    
    // MainStatus
    auto statusIt = mainStatuses.find(id);
    if(statusIt != mainStatuses.end()) atk->setMainStatus(statusIt->second.status, statusIt->second.chance);
    
    // Priorities
    auto priorityIt = priorities.find(id);
    if(priorityIt != priorities.end()) atk->setPriorityLevel(priorityIt->second);
    
    // Crit Level
    auto critIt = critLevels.find(id);
    if(critIt != critLevels.end()) atk->setCriticalLevel(critIt->second);
    
    // Stat changers
    auto statChangerIt = statsChangers.find(id);
    if(statChangerIt != statsChangers.end()) atk->setStatsChanger(statChangerIt->second);
    
    // Hits
    auto hitsIt = hits.find(id);
    if(hitsIt != hits.end()) {
        atk->setMinimumHits(hitsIt->second[0]);
        atk->setMaximumHits(hitsIt->second[1]);
    }
    
    // Recoil
    auto recoilIt = recoils.find(id);
    if(recoilIt != recoils.end()) atk->setRecoilPercentage(recoilIt->second);
    
    // Breaks
    if(breakBefore.count(id) == 1) atk->setBreakBefore(true);
    if(breakAfter.count(id) == 1) atk->setBreakAfter(true);
    
    // Double Damage
    if(doubleDamage.count(id) == 1) atk->setDoublesIfDamaged();
    
    // Always critical
    if(alwaysCriticals.count(id) == 1) atk->setAlwaysCritical();
    
    // Protecting
    if(protects.count(id) == 1) atk->setProtecting();
    
    
    // Return the result
    return atk;
}
