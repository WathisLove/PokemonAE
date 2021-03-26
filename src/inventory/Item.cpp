#include "Item.hpp"
#include "../utility/Logger.hpp"
#include "../Utilities.hpp"
#include "../pokemons/Pokemon.hpp"
#include "items/components/StatBoostComponent.hpp"
#include "items/components/TypeBoostComponent.hpp"
#include "items/components/HealHPComponent.hpp"
#include "items/components/ReviveComponent.hpp"
#include "items/components/HealStatusComponent.hpp"
#include "items/components/HealConfusionComponent.hpp"
#include "items/components/RestorePPComponent.hpp"
#include "items/components/CritBoosterComponent.hpp"
#include "items/components/XPBoostComponent.hpp"
#include "items/components/MoneyBoostComponent.hpp"
#include "items/components/EvoluStatComponent.hpp"
#include "items/components/HappinessBoostComponent.hpp"
#include "items/components/EvolutionComponent.hpp"
#include "items/components/EvBoostComponent.hpp"
#include <cassert>


Item::Item(ItemID id) :
m_id(id){
    setupComponents();
    setupUses();
}



void Item::setupComponents() {
    /// Stat components
    // Add Stat components
    auto statRangeIt = statBoosters.equal_range(m_id);
    for(auto it = statRangeIt.first; it != statRangeIt.second; it++)
        m_components.push_back(new StatBoostComponent(it->second.first, it->second.second));
    
    // Add Specialised Stat components
    auto speStatRangeIt = specialisedStatBoosters.equal_range(m_id);
    for(auto it = speStatRangeIt.first; it != speStatRangeIt.second; it++)
        m_components.push_back(new StatBoostComponent(it->second.stat, it->second.factor, it->second.poke));
    
    // Ev Boosters
    auto evRangeIt = evBoosters.equal_range(m_id);
    for(auto it = evRangeIt.first; it != evRangeIt.second; it++)
        m_components.push_back(new EvBoostComponent(it->second.boost, it->second.stat, it->second.bonusType));
    
    
    /// Type boost components
    // Add Type Boost
    auto typeRangeIt = typeBoosters.equal_range(m_id);
    for(auto it = typeRangeIt.first; it != typeRangeIt.second; it++)
        m_components.push_back(new TypeBoostComponent(it->second.second, Type(it->second.first)));
    
    // Add Type Boost
    auto speTypeRangeIt = specialisedTypeBoosters.equal_range(m_id);
    for(auto it = speTypeRangeIt.first; it != speTypeRangeIt.second; it++)
        m_components.push_back(new TypeBoostComponent(it->second.factor, it->second.type, it->second.poke));
    
    
    /// Heal
    // Fixed healing
    auto hpHealIt = healHPs.find(m_id);
    if(hpHealIt != healHPs.end())
        m_components.push_back(new HealHPComponent(hpHealIt->second));
    
    // Percentage healing
    auto healPercIt = healPercentages.find(m_id);
    if(healPercIt != healPercentages.end())
        m_components.push_back(new HealHPComponent(healPercIt->second));
    
    
    // PPs
    auto ppIt = ppRestored.find(m_id);
    if(ppIt != ppRestored.end())
        m_components.push_back(new RestorePPComponent(ppIt->second));
    
    
    // Revives
    auto reviveIt = revives.find(m_id);
    if(reviveIt != revives.end())
        m_components.push_back(new ReviveComponent(reviveIt->second));
    
    // Specific Status
    auto statusIt = statusHealed.find(m_id);
    if(statusIt != statusHealed.end())
        m_components.push_back(new HealStatusComponent(statusIt->second));
    
    // Any Status (and confusion
    auto anyStatusIt = allStatusHealed.find(m_id);
    if(anyStatusIt != allStatusHealed.end()){
        m_components.push_back(new HealStatusComponent());
        m_components.push_back(new HealConfusionComponent());
    }
    
    
    // Heal confusion
    auto confusionIt = confusionHealed.find(m_id);
    if(confusionIt != confusionHealed.end())
        m_components.push_back(new HealConfusionComponent());
    
    
    // Crit Boost
    auto critBoostIt = critBooster.find(m_id);
    if(critBoostIt != critBooster.end())
        m_components.push_back(new CritBoosterComponent(critBoostIt->second));
    
    
    // XP Boost
    auto xpBoostIt = xpBooster.find(m_id);
    if(xpBoostIt != xpBooster.end())
        m_components.push_back(new XPBoostComponent(xpBoostIt->second));
    
    // Money Boost
    auto moneyBoostIt = moneyBooster.find(m_id);
    if(moneyBoostIt != moneyBooster.end())
        m_components.push_back(new MoneyBoostComponent(moneyBoostIt->second));
    
    // Speed Modifications
    auto speedIt = speedModifier.find(m_id);
    if(speedIt != speedModifier.end())
        m_components.push_back(new StatBoostComponent(StatName::speed, speedIt->second));
    
    // Happiness Boost
    auto happinessIt = happinessBooster.find(m_id);
    if(happinessIt != happinessBooster.end())
        m_components.push_back(new HappinessBoostComponent(happinessIt->second));
    
    // Evolurocs
    auto evoluRange = evoluBoosters.equal_range(m_id);
    for(auto it = evoluRange.first; it != evoluRange.second; it++)
        m_components.push_back(new EvoluStatComponent(it->second.first, it->second.second));
    
    
    /// Evolutions
    // Evolution Stones
    auto evolutionsRanges = stoneEvolutions.equal_range(m_id);
    for(auto it = evolutionsRanges.first; it != evolutionsRanges.second; it++)
        m_components.push_back(new EvolutionComponent(it->second.unevolved, it->second.evolution));
}



void Item::setupUses() {
    /// In Battle
    auto inIt = inBattleUses.find(m_id);
    
    // Set the use in battle
    if(inIt != inBattleUses.end())
        m_useInBattle = inIt->second;
    else{
        Log("Use in battle not set for " + getName().toAnsiString());
        m_useInBattle = UseInBattle::CANNOT_USE;
    }
    
    
    /// OutBattle
    auto outIt = outBattleUses.find(m_id);
    
    // Set the use in battle
    if(outIt != outBattleUses.end())
        m_useOutBattle = outIt->second;
    else{
        Log("Use out battle not set for " + getName().toAnsiString());
        m_useOutBattle = UseOutBattle::CANNOT_USE;
    }
}



const sf::String& Item::getName() const {
    return getName(m_id);
}



ItemID Item::getID() const {
    return m_id;
}



const sf::String& Item::getItemDescription() const {
    // Try to find in the map
    auto it = itemDescriptions.find(m_id);

    // If the Item is in the description Map
    if(it != itemDescriptions.end()){
        return it->second;
    }
    else{
        return itemDescriptions.find(ItemID::LAST_ITEM)->second;
    }
}



ItemCategory Item::getCategory() const {
    // Iterator
    auto it = itemCategories.find(m_id);
    
    if(it != itemCategories.end())
    {
        return it->second;
    }
    else
    {
        Log("Not known category for item" + getName().toAnsiString(), Logger::ERROR);
        return ItemCategory::Object;
    }
}



AttackID Item::getAttackTeached() const {
    return getAttackTeached(m_id);
}



AttackID Item::getAttackTeached(ItemID id) {
    // Check if the Item Learns an attack
    auto attackIt = teachedAttacks.find(id);
    
    // If an attack was found in the map
    if(attackIt != teachedAttacks.end())
        return attackIt->second;
    // Else
    else{
        Log("Can't find a teached attack for Item " + Item::getName(id).toAnsiString(), Logger::ERROR);
        return AttackID::Flammeche;
    }
}



float Item::getCaptureValue() const {
    // Get the capture rate from the map
    auto it = captureRates.find(m_id);
    
    if(it != captureRates.end()){
        return it->second;
    }
    else{
        // Error the method should not be called
        throw std::string("Call to CaptureValue with item " + getName().toAnsiString());
    }
}



bool Item::isUsable() const {
    return m_useOutBattle != UseOutBattle::CANNOT_USE;
}



bool Item::isUsableInFight() const {
    return m_useInBattle != UseInBattle::CANNOT_USE;
}



void Item::onStat(int& statValue, StatName stat, PokemonID holder) const {
    // Call onStat of each component
    for(ItemComponent* component : m_components)
        delete component->onStat(statValue, stat, holder); // Delete even though it should be a null pointer
}



void Item::onDamagesOfType(int& damages, Type attackType, PokemonID attacker) const {
    // Call onDamages of each component
    for(ItemComponent* component : m_components)
        delete component->onDamagesOfType(damages, attackType, attacker); // Delete even though it should be a null pointer
}



std::queue<ItemEffect*> Item::onPokemon(Pokemon* pokemon) const {
    std::queue<ItemEffect*> res;
    
    // Call onPokemon of each component
    for(ItemComponent* component : m_components)
        res.push(component->onPokemon(pokemon));
    
    return res;
}



std::queue<ItemEffect*> Item::onAttack(Attack* attack) const {
    std::queue<ItemEffect*> res;
    
    // Call onAttack of each component
    for(ItemComponent* component : m_components)
        res.push(component->onAttack(attack));
    
    return res;
}



void Item::onCritLevel(int& critLevel) const {
    // Call onCritLevel of each component
    for(ItemComponent* component : m_components)
        delete component->onCritLevel(critLevel); // Delete even though it should be a null pointer
}



void Item::onXPGained(int& xpGained) const {
    // Call onXPGained of each component
    for(ItemComponent* component : m_components)
        delete component->onXPGained(xpGained); // Delete even though it should be a null pointer
}



void Item::onMoneyGained(int& moneyGained) const {
    // Only apply the 2 first effects 
    int count(0);
    
    // Call onMoneyGained of each component
    for(ItemComponent* component : m_components){
        if(count < 2){
            // Apply the effect
            ItemEffect* effect = component->onMoneyGained(moneyGained); 
            
            // Count the effect and delete it 
            if(effect != nullptr){
                count++;
                delete effect;
            }
        }
    }
}



void Item::onHappinessReceived(int& happinessAmount) const {
    // Call onHappinessReceived of each component
    for(ItemComponent* component : m_components)
        delete component->onHappinessReceived(happinessAmount); // Delete even though it should be a null pointer
}



void Item::onEvReceived(int& evAmount, StatName stat) const {
    // Call onEvReceived of each component
    for(ItemComponent* component : m_components)
        delete component->onEvReceived(evAmount, stat); // Delete even though it should be a null pointer
}



bool Item::hasEffectOnPokemon(Pokemon* pokemon) const {
    // Check if there is an effect with any Component
    for(ItemComponent* component : m_components)
        if(component->hasEffectOnPokemon(pokemon))
            return true;
    
    return false;
}



bool Item::hasEffectOnAttack(Attack* attack) const {
    // Check if there is an effect with any Component
    for(ItemComponent* component : m_components)
        if(component->hasEffectOnAttack(attack))
            return true;
    
    return false;
}



UseInBattle Item::getUseInBattle() const {
    return m_useInBattle;
}



UseOutBattle Item::getUseOutBattle() const {
    return m_useOutBattle;
}



bool Item::isGivable() const {
    // For the time being, can't give CTs
    return m_useOutBattle != UseOutBattle::TEACH_MOVE;
}



const sf::String& Item::getName(ItemID id) {
    // Try to find in the map
    auto it = itemNames.find(id);

    if(it != itemNames.end()){
        return it->second;
    }
    else{
        Log("Item name is not in the list (ID : " + toString(static_cast<int>(id)) + ")", Logger::ERROR);
        return itemNames.at(ItemID::LAST_ITEM);
    }
}



ItemID Item::getID(const std::string& str) {
    // Create a sf String for comparison
    sf::String s(str);
    
    // Check if we have a CT
    if(s.substring(0, 2) == "CT"){
        // Get the CT int
        int ctNum = atoi(str.substr(2, str.size()-2).c_str());
        
        // Get the CT ID
        ItemID ctID = (ItemID)(static_cast<int>(ItemID::ct1) + ctNum - 1);
        
        std::cout << "CT " << ctNum << " ID found. CT Name is : " << getName(ctID).toAnsiString() << std::endl;
        return ctID;
    }
    
    // Try to find the str in the map
    for(auto pairIt : itemNames){
        // Check the current map pair
        if(pairIt.second.toAnsiString() == s)
            return pairIt.first;
    }
    
    return ItemID::LAST_ITEM;
}



int Item::getDefaultPrice(ItemID id) {
    // Try to find in the map
    auto priceIt = itemPrices.find(id);
    
    // If the price is in the map
    if(priceIt != itemPrices.end())
        return priceIt->second;
    // Else we put a price of 0
    else{
        std::cout << "Item with no price" << std::endl;
        return 0;
    }
}



int Item::getDefaultSellingPrice(ItemID id) {
    // Divide the buying price by 2
    return Item::getDefaultPrice(id) / 2;
}



ItemCategory Item::getCategory(ItemID id) {
    // Try to find in the map
    auto categoryIt = itemCategories.find(id);
    
    // If the price is in the map
    if(categoryIt != itemCategories.end())
        return categoryIt->second;
    // Else default is Object
    else{
        std::cout << "No category for item" << getName(id).toAnsiString() << std::endl;
        return ItemCategory::Object;
    }
}



sf::IntRect Item::getTextureRect(ItemID item) {
    // rect
    sf::IntRect rect(0,0,32,32);
    
    // Get the Item Id as an int
    int itemVal = static_cast<int>(item);
    
    // Find the row of the Item
    int row = 0;
    for(; row < firstRowItems.size(); row++){
        int rowItem = static_cast<int>(firstRowItems.at(row));
        
        // If we got to the next row 
        if(rowItem > itemVal){
            break;
        }
    }
    // Revert to the row of the current item
    row--;

    // If CT
    if(firstRowItems.at(row) == ItemID::ct1){
        // Get the AttackID
        AttackID attackID = teachedAttacks.at(item);
        Attack* attack = AttackFabric::createAttack(attackID);
        
        // Set the rect Left position
        rect.left = static_cast<int>(attack->getType().getFirstType()) * 32;
        delete attack;
    }
    else{
        // Get the column
        int rowItem = static_cast<int>(firstRowItems.at(row));
        int column = itemVal - rowItem;

        // Set the rect Left position
        rect.left = column * 32;
    }
    
    // Set the rectangle top
    rect.top = row * 32;
    
    // return the Rectangle
    return rect;
}
