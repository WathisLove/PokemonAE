#include "Pokemon.hpp"
#include "PokemonCreator.hpp"
#include <iostream>
#include <cassert>
#include <iostream>
#include "abilities/Ability.hpp"

#include "../utility/Logger.hpp"

// Setup the attacks by level
std::map<PokemonID, std::multimap<int, AttackID> > Pokemon::m_attackByLevel{
    {marcacrin, {
        {0, AttackID::DoublePied},
        {0, AttackID::ComboGriffe},
        {2, AttackID::Belier},
        {6, AttackID::LanceSoleil},
        {6, AttackID::UltraLaser}}},
    {cochignon, {
        {0, AttackID::DoublePied},
        {0, AttackID::ComboGriffe},
        {2, AttackID::Belier},
        {4, AttackID::LanceSoleil}}},
    {mammochon, {
        {0, AttackID::DoublePied},
        {0, AttackID::ComboGriffe},
        {2, AttackID::Belier},
        {4, AttackID::LanceSoleil}}},
    {pikachu, {
        {0, AttackID::Eclair},
        {5, AttackID::ViveAttaque},
        {6, AttackID::UltraLaser},
        {7, AttackID::Gonflette}}},
    {raichu, {
        {0, AttackID::Eclair}}},
    {etourmi, {
        {0, AttackID::ViveAttaque}}},
    {etourvol, {
        {0, AttackID::ViveAttaque}}},
    {etouraptor, {
        {0, AttackID::ViveAttaque}}},
    {mystherbe, {
        {0, AttackID::Charge}}},
    {galekid, {
        {0, AttackID::Charge}}},
    {galegon, {
        {0, AttackID::Charge}}},
    {galeking, {
        {0, AttackID::Charge}}}
        
};



// Setup the attacks by ct
std::map<PokemonID, std::set<AttackID> > Pokemon::m_attacksByCT{
    {marcacrin, {Avalanche, Hypnose}},
    {cochignon, {Avalanche, Hypnose}},
    {mammochon, {Avalanche, Hypnose}},
            
    {pikachu, {UltraLaser}}
};


// Setup the EV yield
std::multimap<PokemonID, EVYield > Pokemon::m_evYields{
    {marcacrin, {attack, 1}},   // Marcacrin
    {cochignon, {attack, 1}},  
    {cochignon, {health, 1}},
    {mammochon, {attack, 3}},  
            
    {pikachu, {speed, 2}},      // Pikachu
    {raichu, {speed, 3}},      
            
    {galekid, {defense, 1}},      // Galekid
    {galegon, {defense, 2}},
    {galeking, {defense, 3}},
            
    {PokemonID::etourmi, {speed, 1}},      // Etourmi
    {PokemonID::etourvol, {speed, 2}},     
    {PokemonID::etouraptor, {attack, 3}},    
            
    {PokemonID::mystherbe, {special_attack, 1}},      // Mystherbe
            
};



// the Evolution Table (empty instantiation)
std::multimap<PokemonID, EvolutionCondition> Pokemon::m_evolutionTable {};


// The Ability Table
std::multimap<PokemonID, PossibleAbility> Pokemon::m_possibleAbilities{
    {pikachu, {AbilityVisibility::ABILITY_COMMON, REGE_FORCE}},
    {marcacrin, {AbilityVisibility::ABILITY_COMMON, ISOGRAISSE}},
    {cochignon, {AbilityVisibility::ABILITY_COMMON, ISOGRAISSE}},
    {mammochon, {AbilityVisibility::ABILITY_COMMON, ISOGRAISSE}},
    {etourmi, {AbilityVisibility::ABILITY_COMMON, INTIMIDATION}},
};



Pokemon::Pokemon(PokemonID id, int level) :
m_id(id),
m_level(level),
m_baseStats(baseStatsOfID(id)),
m_name(pokemonIDtoString(id)),
m_stats(statsAtLevel(*m_baseStats, level)),
m_health(0),
m_mainStatus(),
m_item(nullptr),
m_xpCurrentLvl(0),
m_lastItemUsed(ItemID::LAST_ITEM),
m_ability(AbilityID::UNKNOWN_ABILITY),
m_role(StrategicRole::DEFAULT),
m_confusionTurns(0){
    initializePokemon();
    // Generate a random Sex
    m_sex = generateRandomSex();
    
    // Set the Health
    m_health = getStatValue(health);
    
    // We build the Evolution table in case it wasn't done
    buildEvolutionTable();
}



Pokemon::Pokemon(PokemonID id, int level, int actualHealth)  :
Pokemon(id, level)
{
    m_health = std::max(0, actualHealth);
}



Pokemon::Pokemon(PokemonID id, int level, int actualHealth, PokemonMetadata metadata) :
Pokemon(id, level, actualHealth){
    m_metadata = metadata;
}



Pokemon::~Pokemon() {
    delete m_baseStats;
    delete m_stats;
    
    if(hasItem())
        delete m_item;
}



bool Pokemon::isKO() const {
    return m_health == 0;
}



const sf::String& Pokemon::getName() const {
    return m_name;
}



void Pokemon::setName(const sf::String& string) {
    m_name = string;
}



int Pokemon::getLevel() const {
    return m_level;
}



int Pokemon::getBaseStatValue(StatName stat) const {
    return m_baseStats->getStatValue(stat);
}



int Pokemon::getStatValue(StatName stat) const{
    
    // Get the stat value without modifier
    int statValue = m_stats->getStatValue(stat);
    
    // Check if the nature increase or decrease the given stat
    if(m_nature.isChangingStat()){
        if(m_nature.getLoweredStat() == stat)
            statValue *= 0.9;
        else if(m_nature.getHigheredStat() == stat)
            statValue *= 1.1;
    }
    
    // Apply IVs and EVs
    statValue += m_ivs.getValue(stat) * (m_level / 100.); // Add the total IV at level 100
    
    statValue += m_evs.getValue(stat) / 4;
    
    
    return statValue;
}



int Pokemon::getInFightStat(StatName stat) const{
    // Status and nature Coef
    float statusCoef = 1;
    float natureCoef = 1;
    
    
    // Paralysis reduce the speed
    if(stat == StatName::speed && m_mainStatus.getName() == MainStatusName::Paralysis)
        statusCoef = 0.5;
    
    // Burn reduce the attack
    if(stat == StatName::attack && m_mainStatus.getName() == MainStatusName::Burn)
        statusCoef = 0.5;
    
    // Apply the item effect
    int statVal = getStatValue(stat);
    
    if(hasItem())
        m_item->onStat(statVal, stat, m_id);
    
    return statVal * statusCoef * natureCoef; 
}



PokemonID Pokemon::getID() const {
    return m_id;
}



float Pokemon::getHealthPercentage() const {
    return 100. * m_health / getStatValue(health);
}



float Pokemon::getXPPercentage() const {
    return 100. * m_xpCurrentLvl / (float)getXPNextLevel();
}



TextureHolder::textureID Pokemon::getPokemonTextureID(PokemonID id) {
    switch(id){
        case PokemonID::marcacrin : return TextureHolder::marcacrinTex;
        case PokemonID::cochignon : return TextureHolder::cochignonTex;
        case PokemonID::mammochon : return TextureHolder::mammochonTex;
        case PokemonID::pikachu : return TextureHolder::pikachuTex;
        case PokemonID::raichu : return TextureHolder::raichuTex;
        case PokemonID::etourmi : return TextureHolder::etourmiTex;
        case PokemonID::etourvol : return TextureHolder::etourvolTex;
        case PokemonID::etouraptor : return TextureHolder::etouraptorTex;
        case PokemonID::mystherbe : return TextureHolder::mystherbeTex;
        case PokemonID::galekid : return TextureHolder::galekidTex;
        case PokemonID::galegon : return TextureHolder::galegonTex;
        case PokemonID::galeking : return TextureHolder::galekingTex;
        default : throw "Not known texture for Pokemon " + toString(id); 
    }
}



AttackSet& Pokemon::getAttackSet() {
    return m_attackSet;
}



const Type& Pokemon::getType() const {
    return m_type;
}



bool Pokemon::canLearnByCT(PokemonID pokeID, AttackID id) {
    // Get a reference to the set of CT attack for this pokemon
    try{
        std::set<AttackID>& attacks = m_attacksByCT.at(pokeID);
        
        return attacks.find(id) != attacks.end();
    }
    // If we are out of range, then the pokemon can not learn an attack by CT
    catch(std::out_of_range e){
        return false;
    }
}



std::string Pokemon::getInfoString() const {
    std::string s("===> ");
    
    s += m_name; s += "   Lvl  " + toString(m_level) + "\n";
    s+= "HP : " + toString(m_health) + " / " + toString(getStatValue(StatName::health)) + "\n";
    
    s += "XP : " + toString(m_xpCurrentLvl) + " / " + toString(getXPNextLevel()) + "   (total : " + toString(m_xpTotalEarned) + ")\n";
    
    s+= m_type.getInfoString() + "\n\n";
    
    // STATS
    s += " - STATS -\n";
    s += "Base Stats : \n";
    
    s += m_baseStats->getInfoString() + "\n";
    
    s += "Stats (without EV/IV: \n";
    s += m_stats->getInfoString();
    
    
    s += "Stats : \n";
    s += " H : " + toString(getStatValue(health)) +  + " | A  : " + toString(getStatValue(attack))
        + " | D  : " + toString(getStatValue(defense)) + " | SA : " + toString(getStatValue(special_attack)) 
        + " | SD : " + toString(getStatValue(special_defense)) + " | V : " + toString(getStatValue(speed)) + "\n";
    
    
    // Attacks
    s += m_attackSet.getInfoString();
    
    s += " IV : " + m_ivs.toString();
    
    s += " EV : " + m_evs.toString();
    
    return s;
}



void Pokemon::initializePokemon() {
    setupType();
    
    learnLastAttacksByLevel();
    
    // Set the XP Curve and the Total XP
    setXPCurve();
    m_xpTotalEarned = getXPAtLevel(m_xpCurveType, m_level);
    
    // Setup a common ability by default
    setupCommonAbility();
}



void Pokemon::learnLastAttacksByLevel() {
    // We clear the attack set
    m_attackSet.clear();
    
    // Get a reference to the attacks
    std::multimap<int, AttackID>& levelAttacks = m_attackByLevel.at(m_id);
    
    // And we check the attacks the pokemon learns by level, until we have 4, or reach the end
    for(auto iter = levelAttacks.cbegin(); iter != levelAttacks.end(); iter++){
        if(!m_attackSet.hasPlaceLeft()) return; // Leave if 4 attacks
        
        // If the pokemon has enough levels to learn it
        if(iter->first <= m_level){
            AttackID id = iter->second;
            m_attackSet.addAttack(AttackFabric::createAttack(id));
        }
    }
}



void Pokemon::healEverything() {
    m_health = getStatValue(health);
    
    
    for(int i = 0; i < m_attackSet.getNbAttacks(); i++){
        Attack* a = m_attackSet.getAttack(i);
        a->setPP(a->getPPMax());
    }
    
    cureMainStatus();
}



float Pokemon::getAttackEfficiency(const Attack& attack) const {
    return Type::getDamageMultiplicator(attack.getType(), m_type);
}



bool Pokemon::isAttackStabed(int index) {
    Attack* attack = m_attackSet.getAttack(index);
    
    return isAttackStabed(*attack);
}


bool Pokemon::isAttackStabed(const Attack& attack){
    // Return true if the attack type is one of the pokemon ones
    return m_type.getFirstType() == attack.getType().getFirstType() ||
           m_type.getSecondType() == attack.getType().getSecondType();
}



int Pokemon::calculateDamages(Pokemon& attacker, const Attack& attack, bool critical, int previousDamagesToEnnemy, float coefM) const {
    // Get whether the attack is special, physical or status
    Attack::AttackCategory category = attack.getCategory();
    
    int atk; int def;
    
    if(category == Attack::Physical){
        // Set the values of defense and attack
        atk = attacker.getInFightStat(StatName::attack);
        
        // Keep the min defense between base stat and inFightStat if critical
        def = getInFightStat(StatName::defense);
        if(critical)
            def = std::min(def, getStatValue(StatName::defense));
    }
    else{
        // Set the values of defense and attack
        atk = attacker.getInFightStat(StatName::special_attack);
        
        // Keep the min special defense between base stat and inFightStat if critical
        def = getInFightStat(StatName::special_defense);
        if(critical)
            def = std::min(def, getStatValue(StatName::special_defense));
    }
    
    // Get the other values
    int niv = attacker.getLevel();
    int pui = attack.getDamage(previousDamagesToEnnemy);
    
    
    // Calculate the critical bonus
    float criticalBonus = 1.0;
    if(critical)
        criticalBonus = 1.5;
    
    
    // Calculate the damage range, a factor from 0.8 to 1
    float damageRange = randomFloat(0.8, 1);
    
    // Pv lost
    int pvLost;
    if(pui == 0)
        pvLost = 0;
    else
        pvLost = (int)(coefM * damageRange * criticalBonus * (2 + ((niv*0.4+2)*atk*pui)/(def*50)));
    
    std::cout << "Damage before item " << pvLost << std::endl;
    
    // Apply a boost from the Ennemy item
    if(attacker.hasItem())
        attacker.getItem()->onDamagesOfType(pvLost, attack.getType(), attacker.getID());
    
    std::cout << "Damage after item " << pvLost << std::endl;
    
    // Apply the Attackant Ability
    pvLost = attacker.getAbility().onDamageDealt(pvLost, attack);
    
    std::cout << "Damage after ability " << pvLost << std::endl;
    
    // Return the HP that will be lost
    return pvLost;
}



int Pokemon::receiveAttack(Pokemon& ennemy, const Attack& attack, float coefM, int previousDamagesToEnnemy, bool critical) {  
    // Get the normal damages
    float damages = calculateDamages(ennemy, attack, critical, coefM);
    
    // Apply the Defender ability
    damages = m_ability.onDamageReceived(damages, attack);
    
    m_health -= damages;
    
    if(m_health < 0) 
        m_health = 0;
    
    return (int)damages;
}



int Pokemon::getRandomIntAttack() const {
    return randomInt(0, m_attackSet.getNbAttacks()-1);
}



MainStatus Pokemon::getMainStatus() const {
    return m_mainStatus;
}



void Pokemon::setMainStatus(MainStatus status) {
    m_mainStatus = status;
}



bool Pokemon::hasStatus() const {
    return m_mainStatus.getName() != MainStatusName::NoMainStatus;
}



bool Pokemon::doesStatusDamage() const {
    return m_mainStatus.getDamageFactor() != 0;
}



int Pokemon::getStatusDamages() const {
    return (int)(m_stats->getStatValue(StatName::health) * m_mainStatus.getDamageFactor());
}



void Pokemon::takeStatusDamages() {
    m_health -= getStatusDamages();
    
    if(m_health < 0)
        m_health = 0;
}



void Pokemon::updateTurns() {
    m_mainStatus.updateTurns();
}



void Pokemon::cureMainStatus() {
    m_mainStatus.clearStatus();
}



bool Pokemon::attackThisTurn() {
    bool canAttack = true;
    
    // Check sleep or Freeze 
    if(m_mainStatus.getName() == MainStatusName::Freeze || m_mainStatus.getName() == MainStatusName::Sleep)
        canAttack = false;
    // check Paralysis
    else if(m_mainStatus.getName() == MainStatusName::Paralysis)
        canAttack = !(randomInt(0, 3) == 0);
    
    return canAttack;
}



void Pokemon::leaveFight() {
    // Reset the statChanger
    m_statChanger = StatsChanger();
}



void Pokemon::addStatChanger(StatsChanger stChanger) {
    m_statChanger.add(stChanger);
}



const Stats& Pokemon::getStats() {
    return *m_stats;
}



StatsChanger Pokemon::getStatChanger() const {
    return m_statChanger;
}



int Pokemon::getHealth() {
    return m_health;
}



int Pokemon::healHP(int value) {
    // Store the previous HP amount
    int m_prevHealth = m_health;
    
    // Heal
    m_health = std::min(value + m_health, getStatValue(StatName::health));
    
    // Return the difference
    return m_health - m_prevHealth;
}



int Pokemon::healRatio(float coeff) {
    // Get the MAx health
    int maxHP = getStatValue(StatName::health);
    
    // Heal 
    return healHP((int)(maxHP * coeff));
}



void Pokemon::setHP(int val) {
    if(val < 0)
        m_health = 0;
    else if(val > getStatValue(StatName::health))
        m_health = getStatValue(StatName::health);
    else
        m_health = val;
}



bool Pokemon::isFullHP() {
    return m_health == getStatValue(StatName::health);
}



Item* Pokemon::getItem() {
    if(!hasItem())
        throw std::string("The pokemon " + m_name + " doesn't have any item");
    
    return m_item;
}



bool Pokemon::hasItem() const {
    return (m_item != nullptr);
}



Item* Pokemon::takeItem() {
    if(!hasItem())
        throw std::string("The pokemon " + m_name + " doesn't have any item");
    
    Item* item = m_item;
    
    m_item = nullptr;
    
    return item;
}



void Pokemon::giveItem(Item* item) {
    // Check if we already have an item
    if(hasItem())
        throw std::string("The pokemon " + m_name + " already holds " + m_item->getName().toAnsiString());
    
    else if(item == nullptr)
        throw std::string("Trying to give a nullptr object to " + m_name);
    
    // Else set the pointer to the new item
    m_item = item;
}



void Pokemon::swapItem(Pokemon* p) {
    if(hasItem()){
        Item* oldIt = takeItem();
        if(p->hasItem()){
            Item* newIt = p->takeItem();
            
            p->giveItem(oldIt);
            giveItem(newIt);
        }
        else{
            p->giveItem(oldIt);
        }
    }
    else{
        if(p->hasItem()){
            Item* it = p->takeItem();
            giveItem(it);
        }
    }
    
    // Check if we have the good items after the switch
    if(hasItem())
        std::cout << m_name.toAnsiString() << " now has a " << m_item->getName().toAnsiString() << std::endl;
    else
        std::cout << m_name.toAnsiString() << " now has no item" << std::endl;
    
    if(p->hasItem())
        std::cout << p->getName().toAnsiString() << " now has a " << m_item->getName().toAnsiString() << std::endl;
    else
        std::cout << p->getName().toAnsiString() << " now has no item" << std::endl;
}



bool Pokemon::isTouchedByAttack(Attack* attack) {
    // The pokemon is not touched uf the damage multiplicator is equal to 0
    return (Type::getDamageMultiplicator(attack->getType(), getType()) != 0);
}



int Pokemon::giveXp(int xpPoints) {    
    // Only update if the level is below 100
    if(m_level == 100)
        return 0;
    
    // Get the number of xp left to the next level
    int xpToNext = getXPNextLevel() - m_xpCurrentLvl;
        
    // If there is not enough xp
    if(xpPoints < xpToNext){
        m_xpCurrentLvl += xpPoints;
        m_xpTotalEarned += xpPoints;
        return 0;
    }
    //Else we get a level
    else{
        levelUp();
        return xpPoints - xpToNext;
    }
}



void Pokemon::levelUp() {
    // Only update if the level is below 100
    if(m_level == 100)
        return;
        
    // Update current xp and level
    m_level++;
    m_xpCurrentLvl = 0;
    m_xpTotalEarned = getXPAtLevel(m_xpCurveType, m_level);
    
    // Get the Health percentage to update the health points
    float healthRatio = getHealthPercentage();
    
    // Update the stats
    delete m_stats;
    m_stats = statsAtLevel(*m_baseStats, m_level);
    
    
    // Update the health
    // get the current Health
    float previousHealth = m_health;
    float max = getStatValue(StatName::health);
    
    // Map the Health between the old value and the new max
    m_health = limit((float)(getStatValue(StatName::health) * (healthRatio / 100.)), previousHealth, max);
}



void Pokemon::setXPCurve() {
    switch(m_id){
        case PokemonID::marcacrin :
        case PokemonID::cochignon :
        case PokemonID::mammochon :
        case PokemonID::galekid :
        case PokemonID::galegon :
        case PokemonID::galeking :
            m_xpCurveType = XPCurveType::XP_Slow;
            break;
                
        case PokemonID::mystherbe :
        case PokemonID::etourmi :
        case PokemonID::etourvol :
        case PokemonID::etouraptor :
            m_xpCurveType = XPCurveType::XP_MediumSlow;
            break;
            
        case PokemonID::pikachu :
        case PokemonID::raichu :
            m_xpCurveType = XPCurveType::XP_MediumFast;
            break;
        default:
            throw "No xp curve for Pokemon with ID " + toString(m_id);
    }
}



int Pokemon::getBaseExperienceYield(PokemonID id) {
    switch(id){
        case PokemonID::marcacrin :
            return 50;
        case PokemonID::cochignon :
            return 158;
        case PokemonID::mammochon :
            return 239;
                
        case PokemonID::pikachu :
            return 112;
        case PokemonID::raichu :
            return 218;
        case PokemonID::mystherbe :
            return 78;
        case PokemonID::etourmi :
            return 56;
        case PokemonID::etourvol :
            return 113;
        case PokemonID::etouraptor :
            return 172;
        case PokemonID::galekid :
            return 96;
        case PokemonID::galegon :
            return 152;
        case PokemonID::galeking :
            return 205;
        default:
            throw "No Base XP for Pokemon with ID " + toString(id);
    }
}



int Pokemon::getExperiencePointsYield(bool wild, bool luckyEgg) {

    // Check if we have a wild pokemon
    float coeffWild = 1.5;
    if(wild) coeffWild = 1;
    
    // Get the Base XP
    int baseXP = getBaseExperienceYield(m_id);
    
    // Coeff if the lucky Egg is hold
    float coeffLuckyEgg = 1;
    if(luckyEgg) coeffLuckyEgg = 1.5;
    
    // Check the Affection LEvel
    float coeffAffection = 1;
    
    
    // Coeff for the XP Share
    float coeffXPShare = 1; 
    
    
    return coeffWild * baseXP * coeffLuckyEgg * m_level * coeffAffection / (7 * coeffXPShare);
}



bool Pokemon::hasAnyPPLeft() {
    // Chck each attack to see if it has PPs lefts
    for(int i = 0; i < m_attackSet.getNbAttacks(); i++){
        Attack* attack = m_attackSet.getAttack(i);
        
        if(attack->getPP() > 0){
            return true;
        }
    }
    
    // Else return false
    return false;
}



int Pokemon::getXPCurrentLevel() {
    return m_xpCurrentLvl;
}



int Pokemon::getXPNextLevel() const {
    return getXPToNextLevel(m_xpCurveType, m_level);
}



void Pokemon::setMetadata(PokemonMetadata metadata) {
    m_metadata = metadata;
}



PokemonMetadata& Pokemon::getMetadata() {
    return m_metadata;
}



PokemonNature& Pokemon::getNature() {
    return m_nature;
}



void Pokemon::setNature(PokemonNature::NatureID id) {
    m_nature = PokemonNature(id);
}



bool Pokemon::canReproduce() {
    return m_sex != PokemonSex::Sx_None;
}



int Pokemon::getCaptureRate() {
    switch(m_id){
        case PokemonID::marcacrin:
            return 225;
        case PokemonID::cochignon:
            return 75;
        case PokemonID::mammochon:
            return 50;
                    
        case PokemonID::pikachu:
            return 190;
        
        default:
            std::cout << "Unknown capture rate for ID " + toString(static_cast<int>(m_id)) << std::endl;
            return 255;
    }
}



void Pokemon::sufferRecoil(int recoilPercentage) {
    // Get the damages dealt
    int damage = recoilPercentage * getStatValue(health) / 100.;
    
    // Deal the damages
    m_health -= damage;
    
    // Make sure to keep health >= 0
    if(m_health < 0) 
        m_health = 0;
}



float Pokemon::getCriticalChance(int attackCricitalLevel) {
    // Return the chance to make a critical hit
    if(attackCricitalLevel == 1)
        return 1/16.;
    else if(attackCricitalLevel == 2) 
        return 1/8.;
    else if(attackCricitalLevel == 3)
        return 1/4.;
    else if(attackCricitalLevel == 4)
        return 1/3.;
    else
        return 1/2.;
}



void Pokemon::replaceAttack(int index, AttackID newAttack) {
    // check if the index is correct
    if(index < 0 || index > 3)
        throw "Invalid index " + toString(index) + " for replacing the attack";
    
    // Replace the Attack
    m_attackSet.replaceAttack(index, newAttack);
}



std::set<AttackID> Pokemon::getAttacksSinceLevel(int lastLevel) {
    // Get a reference to the attacks
    std::multimap<int, AttackID>& levelAttacks = m_attackByLevel.at(m_id);
    
    // A set of AttackID for the result
    std::set<AttackID> res;
    
    // And we check the attacks the pokemon learns by level, until we have 4, or reach the end
    for(auto iter = levelAttacks.cbegin(); iter != levelAttacks.end(); iter++){
        // If the pokemon has enough levels to learn it
        if(iter->first > lastLevel && iter->first <= m_level){
            // We check if the pokemon doesn't already know the attack
            if(!m_attackSet.contains(iter->second)){
                // Insert the AttackID in the set
                res.insert(iter->second);
            }
        }
    }
    
    // Return the result set
    return res;
}



ItemID Pokemon::getLastItemUsed() {
    return m_lastItemUsed;
}



bool Pokemon::hasEvolution(PokemonID pokemon) {
    // Get an iterator to all the evolutions of the pokemon
    auto pair = m_evolutionTable.equal_range(pokemon);
    
    // There is an evolution if the range is >= 1
    return pair.first != pair.second;
}



bool Pokemon::canEvolve() {
    // Get an iterator to all the evolutions of the pokemon
    auto pair = m_evolutionTable.equal_range(m_id);
    
    // Check each of the evolutions
    for(auto it = pair.first; it != pair.second; it++){
        // Get the evolution
        EvolutionCondition& evo = it->second;
        
        // Test it
        if(evo.completesConditions(this))
            return true;
    }
    
    // Else we found no valid evolution 
    return false;
}



PokemonID Pokemon::getEvolutionID() {
    // Get an iterator to all the evolutions of the pokemon
    auto pair = m_evolutionTable.equal_range(m_id);
    
    // Check each of the evolutions
    for(auto it = pair.first; it != pair.second; it++){
        // Get the evolution
        EvolutionCondition& evo = it->second;
        
        // Test it 
        if(evo.completesConditions(this)){
            // Return the Evolution ID if it is valid
            return evo.getEvolutionID();
        }
    }
    
    // Else throw a message because there was no correct evolution
    throw "No evolution possible for PokemonID " + toString(m_id);
}



Pokemon* Pokemon::evolve(PokemonID evolutionID) {
    // Create the pokemon with the same health, level and metadata
    Pokemon* evolution = createPokemon(evolutionID, m_level, m_health, m_metadata);
    
    // Set the pokemon nature, name and XP
    evolution->m_nature = m_nature;
    evolution->m_name = m_name;
    evolution->m_xpTotalEarned = m_xpTotalEarned;
    evolution->m_xpCurrentLvl = m_xpCurrentLvl;
    
    // Set the sex, status and stat changers
    evolution->m_sex = m_sex;
    evolution->m_mainStatus = m_mainStatus;
    evolution->m_statChanger = m_statChanger;
    
    // Copy EVs and IVs
    evolution->m_evs = m_evs;
    evolution->m_ivs = m_ivs;
    
    // Learn some attacks
    evolution->getAttackSet().clear();
    for(int i =0; i < m_attackSet.getNbAttacks(); i++){
        Attack* a = m_attackSet.getAttack(i);
        
        // Create a copy of the attack
        Attack* newAtk = AttackFabric::createAttack(a->getID());
        newAtk->setPP(a->getPP());
        newAtk->setPPMax(a->getPPMax());
        
        // Add it to the set
        evolution->getAttackSet().addAttack(newAtk);
    }
    
    // Set the item
    if(m_item != nullptr){
        Item* item = new Item(m_item->getID());
        evolution->m_item = item;
    }
    
    // Set the last Item used
    evolution->m_lastItemUsed = m_lastItemUsed;
    
    // Set the Health
    evolution->m_health = getHealthPercentage() * evolution->getStatValue(health) / 100.;
    
    // Return the evolved pokemon
    return evolution;
}



void Pokemon::setAbility(AbilityID id) { 
    m_ability = Ability(id);
}



void Pokemon::setRandomAbility(bool allowHiddenAbility) {
    // If the Hidden ability is forbidden, just setup a common one
    if(!allowHiddenAbility)
        setupCommonAbility();
    
    // Get all abilites for the pokemon
    std::vector<AbilityID> abilities;
    
    // Get the possible abilities for the current pokemon
    auto itRange = m_possibleAbilities.equal_range(m_id);
    
    for(auto it = itRange.first; it != itRange.second; it++)
        abilities.push_back(it->second.id);
    
    // Randomly set a common ability from the vector
    int choice = randomInt(0, abilities.size()-1);
    
    // Set the ability
    setAbility(abilities.at(choice));
}



Ability& Pokemon::getAbility() {
    return m_ability;
}



EVSet& Pokemon::getEVs() {
    return m_evs;
}

void Pokemon::setEVSet(const EVSet& set) {
    m_evs = set;
}



IVSet& Pokemon::getIVs() {
    return m_ivs;
}

void Pokemon::setIVSet(const IVSet& set) {
    m_ivs = set;
}


void Pokemon::addEVYielded(PokemonID killed) {
    // Map for the result EVs
    std::map<StatName, int> evs;
    
    // Get the iterators to the range
    auto pair = m_evYields.equal_range(killed);
    
    // Go through the range
    for(auto it = pair.first; it != pair.second; it++){
        // Get the stat and value
        StatName stat = it->second.stat;
        int value= it->second.value;
        
        evs[stat] = value;
    }
    
    // For each stat, put a default value, apply the item and give the EVs to the pokemon
    for(StatName stat : {StatName::attack, StatName::defense, StatName::special_attack, StatName::special_defense, StatName::speed, StatName::health}){
        // By default, put a 0
        if(evs.find(stat) == evs.end())
            evs[stat] = 0;
        
        // Apply the item
        if(hasItem())
            m_item->onEvReceived(evs.at(stat), stat);
        
        // Give the EVs to the pokemon
        if(m_evs.canIncrease(stat)){
            Log("Gained " + toString(evs.at(stat)) + " EV in " + toString(static_cast<int>(stat)));
            m_evs.add(stat, evs.at(stat));
        }
    }
}



StrategicRole Pokemon::getRole() const {
    return m_role;
}



void Pokemon::setRole(StrategicRole role) {
    m_role = role;
}



bool Pokemon::isConfused() {
    return m_confusionTurns > 0;
}



void Pokemon::setConfused(int turns) {
    assert(turns >= 0);
    
    m_confusionTurns = turns;
}



PokemonSex Pokemon::getSex() {
    return m_sex;
}



void Pokemon::setSex(PokemonSex sex) {
    m_sex = sex;
}



void Pokemon::setupType() {
    switch(m_id){
        case marcacrin:
        case cochignon:
        case mammochon:
            m_type = Type(Type::Ice, Type::Ground);
            break;
        case pikachu:
        case raichu:
            m_type = Type(Type::Electric);
            break;
        case etourmi:
        case etourvol:
            m_type = Type(Type::Flying, Type::Normal);
            break;
        case etouraptor:
            m_type = Type(Type::Flying, Type::Fighting);
            break;
        case mystherbe:
            m_type = Type(Type::Grass, Type::Poison);
            break;
        case galekid:
        case galegon:
        case galeking:
            m_type = Type(Type::Steel, Type::Rock);
            break;
        default:
            throw "Can't give a type to the pokemon with ID " + toString(m_id);
    }
}



void Pokemon::buildEvolutionTable() {
    // We quit if the evolution table is not empty
    if(!m_evolutionTable.empty())
        return;
    
    // Marcacrin to Cochignon
    EvolutionCondition evo(PokemonID::cochignon);
    evo.addLevelCondition(6);
    m_evolutionTable.insert(std::pair<PokemonID, EvolutionCondition>(PokemonID::marcacrin, evo));
    
    // Evolution from Pikachu to raichu
    evo = EvolutionCondition(PokemonID::raichu);
    evo.addItemUseCondition(ItemID::pierreFoudre);
    m_evolutionTable.insert(std::pair<PokemonID, EvolutionCondition>(PokemonID::pikachu, evo));
}



void Pokemon::setupCommonAbility() {
    // Exit and leave No Ability if there is none
    if(m_possibleAbilities.count(m_id) == 0){
        std::cout << "No abilities for " << m_name.toAnsiString() << ". Keeping UNKNOWN" << std::endl;
        return;
    }
    
    // Get the possible abilities for the current pokemon
    auto itRange = m_possibleAbilities.equal_range(m_id);
    
    
    // Get the Common abilities
    std::vector<AbilityID> abilities;
    
    for(auto it = itRange.first; it != itRange.second; it++)
        if(it->second.visibility == AbilityVisibility::ABILITY_COMMON)
            abilities.push_back(it->second.id);
    
    
    // Randomly set a common ability from the vector
    int choice = randomInt(0, abilities.size()-1);
    
    
    // Set the ability
    setAbility(abilities.at(choice));
}
