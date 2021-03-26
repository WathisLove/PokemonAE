#include "Ability.hpp"
#include "../Pokemon.hpp"
#include "../attacks/StatsChanger.hpp"

/**
 * Creates the Ability Name map
 */
std::map<AbilityID, sf::String> Ability::m_names {
    {AbilityID::UNKNOWN_ABILITY, sf::String(L"Undefined Ability")},
    {AbilityID::INTIMIDATION, sf::String(L"Intimidation")},
    {AbilityID::ISOGRAISSE, sf::String(L"Isograisse")},
    {AbilityID::REGE_FORCE, sf::String(L"Régé-Force")}
};

/**
 * Creates the Ability Description map
 */
std::map<AbilityID, sf::String> Ability::m_descriptions {
    {AbilityID::UNKNOWN_ABILITY, sf::String(L"Unknown description")},
    {AbilityID::INTIMIDATION, sf::String(L"Baisse l'attaque de l'ennemi en arrivant au combat.")},
    {AbilityID::INTIMIDATION, sf::String(L"Le pokemon résiste aux attaques Feu et Glace.")},
    {AbilityID::REGE_FORCE, sf::String(L"Le pokémon récupère une partie de ses PV lorsqu'il est échangé au combat.")}
};



/**
 * Creates the Ability OnDamageReceived Map
 */
std::map<AbilityID, std::function<float(float, const Attack&)> > Ability::m_onDamageReceived{
    std::make_pair(ISOGRAISSE, [](float damage, const Attack& atk) 
    {   Type::TypeName type = atk.getType().getFirstType(); 
        if(type == Type::Fire || type == Type::Ice) return std::max(1.f, damage /= 2.); 
        else return damage;
    })
};


/**
 * Creates the Ability OnDamageDealt Map
 */
std::map<AbilityID, std::function<float(float, const Attack&)> > Ability::m_onDamageDealt{

};


/**
 * Creates the Ability AllowEnnemySwitch Map
 */
std::map<AbilityID, std::function<bool(const Pokemon&)> > Ability::m_allowEnnemySwitch{
    
};


/**
 * Creates the Ability OnLeavingSwitch Map
 */
std::map<AbilityID, std::function<void(Pokemon*)> > Ability::m_onLeavingSwitch{
    std::make_pair(REGE_FORCE, [](Pokemon* p) { p->healRatio(0.3); }),
};



/**
 * Creates the Ability OnEnteringFight Map
 */
std::map<AbilityID, std::function<AbilityEffect(const Pokemon&, const Pokemon&)> > Ability::m_onEnteringFight{
    std::make_pair(INTIMIDATION, [](const Pokemon& owner, const Pokemon& ennemy) 
    { return AbilityEffect(StatsChanger(Team::ennemy, -1,0,0,0,0,0, 0)); }),
};



Ability::Ability(AbilityID id) :
m_id(id){
    //m_allowEnnemySwitch.emplace(std::make_pair(id, [](Pokemon* p) {return true;}));

}



sf::String& Ability::getDescription() {
    // Check if the Description is in the map
    if(m_descriptions.find(m_id) != m_descriptions.end()){
        return m_descriptions.at(m_id);
    }
    else
        return m_descriptions.at(AbilityID::UNKNOWN_ABILITY);
}



sf::String& Ability::getName() {
    // Check if the Name is in the map
    if(m_names.find(m_id) != m_names.end()){
        return m_names.at(m_id);
    }
    else
        return m_names.at(AbilityID::UNKNOWN_ABILITY);
}



AbilityID Ability::getID() {
    return m_id;
}



float Ability::onDamageReceived(float damage, const Attack& attack) {
    // Check if there is an entry in DamageReceived Map
    if(m_onDamageReceived.find(m_id) != m_onDamageReceived.end())
        return m_onDamageReceived.at(m_id)(damage, attack);
    else
        return damage;
}



float Ability::onDamageDealt(float damage, const Attack& attack) {
    // Check if there is an entry in DamageDealt Map
    if(m_onDamageDealt.find(m_id) != m_onDamageDealt.end())
        return m_onDamageDealt.at(m_id)(damage, attack);
    else
        return damage;
}



bool Ability::allowEnnemySwitch(const Pokemon& ennemy) {
    // Check if there is an entry in AllowScitch Map
    if(m_allowEnnemySwitch.find(m_id) != m_allowEnnemySwitch.end())
        return m_allowEnnemySwitch.at(m_id)(ennemy);
    else
        return true;
}



void Ability::onLeavingSwitch(Pokemon* owner) {
    // Check if there is an entry in AllowScitch Map
    if(m_onLeavingSwitch.find(m_id) != m_onLeavingSwitch.end())
        m_onLeavingSwitch.at(m_id)(owner);
}



AbilityEffect Ability::onEnteringFight(const Pokemon& owner, const Pokemon& ennemy) {
    // Apply the ability if it has effect on entering the fight
    if(m_onEnteringFight.find(m_id) != m_onEnteringFight.end()){
        return m_onEnteringFight.at(m_id)(owner, ennemy);
    }
    // Else return an empty string
    else
        return AbilityEffect();
}
