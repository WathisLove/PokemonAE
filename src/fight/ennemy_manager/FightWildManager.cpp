#include "FightWildManager.hpp"


FightWildManager::FightWildManager(Pokemon* p) :
m_pokemon(p){

}



void FightWildManager::endFight(bool winner) {
    // If the sauvage pokemon won, we destroy it
    if(winner)
        delete m_pokemon;
}



FightAction FightWildManager::getNextAction(Pokemon* ennemy, bool canSwitch) {
    // For the moment, a wild pokemon only attacks
    return FightAction::FA_Attack;     
}



int FightWildManager::getNextAttackIndex() {
    // For the moment, a wild pokemon uses random attacks
    return m_pokemon->getRandomIntAttack();
}



bool FightWildManager::hasPokemonsNotKO() {
    return !m_pokemon->isKO();
}



int FightWildManager::getFirstPokemonNotKO() {
    return 0;
}



Pokemon* FightWildManager::getCurrentPokemon() {
    return m_pokemon;
}



bool FightWildManager::playerCanFlee() {
    return true;
}



bool FightWildManager::canBeCaptured() {
    return true;
}



bool FightWildManager::isTrainer() {
    return false;
}



ItemID FightWildManager::getItemToUse() const {
    throw("WildManager getItem to Use should not be called cause it doesn't make sense");
}



int FightWildManager::bouncesNumber(int captureRate) {
    // Calcultate b : the higher the more chances to capture
    int b = 65536 / pow((255./captureRate), 0.1875);
    
    for(int i = 0; i < 4; i++){
        // Get a random value 
        int r = randomInt(0, 65536); 
        
        // If the random number is higher, there are no more bounces
        if(r > b)
            return i;
    }
    
    // Else we return 4 and it's a capture
    return 4;
}



int FightWildManager::captureRate(float ballRate) {
    
    //Get the HP and HP Max
    int healthMax = m_pokemon->getStatValue(health);
    int health = m_pokemon->getHealth();
    
    
    // Get the pokemon capture rate
    int rate = m_pokemon->getCaptureRate();
    
    // Bonus gven by the status
    float statusBonus = m_pokemon->getMainStatus().getCaptureBonus();
    
    
    // Calculate the capture rate
    return (3*healthMax - 2*health) * rate * ballRate * statusBonus / (3*healthMax);
}
