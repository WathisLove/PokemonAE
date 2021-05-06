#include "Attack.hpp"

Attack::Attack(AttackID id, const sf::String& name, Type type, AttackCategory category, AttackTarget target, const sf::String& description) :
m_id(id),
m_name(name),
m_category(category),
m_target(target),
m_type(type),
m_accuracy(100),
m_damage(0),
m_ppMax(40),
m_pp(40),
m_priorityLevel(0),
m_recoilPercentage(0),
m_breakBefore(false),
m_breakAfter(false),
m_minimumHits(1),
m_maximumHits(1),
m_mainStatus(MainStatusName::NoMainStatus),
m_mainStatusChance(0),
m_statsChanges(),
m_criticalLevel(1),
m_alwaysCritical(false),
m_isProtecting(false),
m_doubleIfDamaged(false),
m_description(description)
{

}



bool Attack::succeeded() const {
    float randomN = randomInt(1, 100);
    
    // Return false if the attack failed, true if between [1 ; accuracy]
    return !(randomN > m_accuracy);
}



void Attack::usePP(int n) {
    m_pp -= n;
    
    if(m_pp < 0) m_pp = 0;
}



int Attack::getAccuracy() const {
    return m_accuracy;
}



int Attack::getDamage(int previousDamagesToEnnemy) const {
    // Multiply the damages by 2 if needed
    if(isDoublingIfDamaged() && previousDamagesToEnnemy > 0)
        return m_damage * 2;
    
    // Else return default damages
    return m_damage;
}



const sf::String& Attack::getName() const {
    return m_name;
}

int Attack::getPP() const {
    return m_pp;
}

int Attack::getPPMax() const {
    return m_ppMax;
}



void Attack::setAccuracy(int accuracy) {
    m_accuracy = accuracy;
}



void Attack::setDamage(int damage) {
    m_damage = damage;
}



void Attack::setMaxAccuracy() {
    m_accuracy = 500;
}



void Attack::setPP(int pp) {
    m_pp = pp;
    
    if(m_pp > m_ppMax)
        m_pp = m_ppMax;
}



void Attack::setPPMax(int ppMax) {
    m_ppMax = ppMax;
    m_pp = ppMax;;
}



Type Attack::getType() const {
    return m_type;
}


std::string Attack::getInfoString() const {
    return m_name.toAnsiString() + " (" + toString((int)m_id) + ")   Dmg : " + toString(m_damage) + "   PPs : " + toString(m_pp) + "/" + toString(m_ppMax);
}



Attack::AttackCategory Attack::getCategory() const {
    return m_category;
}



std::wstring Attack::getEfficiencyDialog(float coef) {
    if(coef == 0) return L"Ça n'affecte pas le pokemon adverse...";
    else if(coef < 1) return L"Ce n'est pas très efficace.";
    else if(coef > 1) return L"C'est super efficace !";
    else return L"Unknown sentence for coef";
}



void Attack::setMainStatus(MainStatusName name, float chance) {
    m_mainStatus = name;
    m_mainStatusChance = chance;
}



bool Attack::canDealStatus() const {
    return m_mainStatus != MainStatusName::NoMainStatus;
}



bool Attack::canAsleep() const {
    return m_mainStatus == MainStatusName::Sleep;
}



bool Attack::canBadlyPoison() const {
    return m_mainStatus == MainStatusName::BadlyPoison;
}



bool Attack::canBurn() const {
    return m_mainStatus == MainStatusName::Burn;
}



bool Attack::canFreeze() const {
    return m_mainStatus == MainStatusName::Freeze;
}



bool Attack::canParalyse() const {
    return m_mainStatus == MainStatusName::Paralysis;
}



bool Attack::canPoison() const {
    return m_mainStatus == MainStatusName::Poison;
}



float Attack::getAsleepChance() const {
    if(canAsleep())
        return m_mainStatusChance;
    else
        return 0.0;
}



void Attack::restorePPs(int amount) {
    if(amount == -1){
        m_pp = m_ppMax;
    }
    else{
        m_pp = std::min(m_pp + amount, m_ppMax);
    }
}



float Attack::getBadlyPoisonChance() const {
    if(canBadlyPoison())
        return m_mainStatusChance;
    else
        return 0.0;
}



float Attack::getBurnChance() const {
    if(canBurn())
        return m_mainStatusChance;
    else
        return 0.0;
}



float Attack::getFreezeChance() const {
    if(canFreeze())
        return m_mainStatusChance;
    else
        return 0.0;
}



float Attack::getParalyseChance() const {
    if(canParalyse())
        return m_mainStatusChance;
    else
        return 0.0;
}



float Attack::getPoisonChance() const {
    if(canPoison())
        return m_mainStatusChance;
    else
        return 0.0;
}



std::vector<StatsChanger> Attack::getStatChangerAsVector() const {
    return m_statsChanges.getStatChangerAsVector();
}



const StatsChanger& Attack::getStatsChanger() const {
    return m_statsChanges;
}



void Attack::setStatsChanger(StatsChanger statChanger) {
    m_statsChanges = statChanger;
}



sf::IntRect Attack::getCategoryTextureRect() {
    return getCategoryTextureRect(m_category);
}



sf::IntRect Attack::getCategoryTextureRect(AttackCategory category) {
    if(category == AttackCategory::Physical){
        return sf::IntRect(0, 0, 128, 64);
    }
    else if(category == AttackCategory::Special){
        return sf::IntRect(0, 64, 128, 64);
    }
    else{
        return sf::IntRect(0, 128, 128, 64);
    }
}



void Attack::setPriorityLevel(int level) {
    m_priorityLevel = level;
}



void Attack::setRecoilPercentage(int percentage) {
    m_recoilPercentage = percentage;
}



void Attack::setBreakAfter(bool breakAfter) {
    m_breakAfter = breakAfter;
}



void Attack::setBreakBefore(bool breakBefore) {
    m_breakBefore = breakBefore;
}



void Attack::setMinimumHits(int minHits) {
    m_minimumHits = minHits;
}



void Attack::setMaximumHits(int maxHits) {
    m_maximumHits = maxHits;
}



void Attack::setProtecting() {
    m_isProtecting = true;
}



void Attack::setDoublesIfDamaged() {
    m_doubleIfDamaged = true;
}



int Attack::getPriority() {
    return m_priorityLevel;
}



int Attack::getRecoilPercentage() {
    return m_recoilPercentage;
}



bool Attack::getBreakAfter() {
    return m_breakAfter;
}



bool Attack::getBreakBefore() {
    return m_breakBefore;
}



int Attack::getMaximumHits() {
    return m_maximumHits;
}



int Attack::getCriticalLevel() {
    return m_criticalLevel;
}



void Attack::setCriticalLevel(int level) {
    // Check if the level is correct
    if(level < 1 || level > 5)
        throw "Can't have an attack critical level of " + toString(level);
    
    // Set the level
    m_criticalLevel = level;
}



bool Attack::isAlwaysCritical() {
    return m_alwaysCritical;
}




void Attack::setAlwaysCritical() {
    m_alwaysCritical = true;
}



int Attack::getMinimumHits() {
    return m_minimumHits;
}



bool Attack::hasRecoil() {
    return m_recoilPercentage > 0;
}



bool Attack::isMultiHitAttack() {
    return m_minimumHits > 1;
}



AttackID Attack::getID() {
    return m_id;
}



bool Attack::isProtectingPokemon() {
    return m_isProtecting;
}



bool Attack::isDoublingIfDamaged() const {
    return m_doubleIfDamaged;
}



const sf::String& Attack::getDescription() const {
    return m_description;
}
