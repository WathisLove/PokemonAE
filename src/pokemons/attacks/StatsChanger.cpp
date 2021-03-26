#include "StatsChanger.hpp"
#include "Attack.hpp"



StatsChanger::StatsChanger() :
m_targetTeam(Team::ennemy),
m_attack(0),
m_defense(0),
m_specialAttack(0),
m_specialDefense(0),
m_speed(0),
m_accuracy(0),
m_evasion(0){

}


StatsChanger::StatsChanger(Team targetTeam, int atk, int def, int speAtk, int speDef, int speed, int evas, int accur) : 
m_targetTeam(targetTeam),
m_attack(atk),
m_defense(def),
m_specialAttack(speAtk),
m_specialDefense(speDef),
m_speed(speed),
m_accuracy(accur),
m_evasion(evas){

}



int StatsChanger::getStatChangerValue(StatName stat) const {
    switch(stat){
        case StatName::attack : return m_attack;
        case StatName::defense : return m_defense;
        case StatName::special_attack : return m_specialAttack;
        case StatName::special_defense : return m_specialDefense;
        case StatName::speed : return m_speed;
        case StatName::accuracy : return m_accuracy;
        case StatName::evasion : return m_evasion;
    }
    
    throw std::string("Not known StatChanger value for ") + toString(static_cast<int>(stat));
}



void StatsChanger::setStatChangerValue(StatName stat, int val) {
    // SEt the stat to the value *val*
    switch(stat){
        case StatName::attack : m_attack = val;
        break;
        case StatName::defense : m_defense = val;
        break;
        case StatName::special_attack : m_specialAttack = val;
        break;
        case StatName::special_defense : m_specialDefense = val;
        break;
        case StatName::speed : m_speed = val;
        break;
        case StatName::accuracy : m_accuracy = val;
        break;
        case StatName::evasion : m_evasion = val;
        break;
    }
}



int StatsChanger::getFinalStat(StatName stat, int baseStat) const {
    // get the value from -6 to +6
    int val = getStatChangerValue(stat);
    
    float coef(1);
    
    // Return the new value of the statistic
    if(stat == StatName::accuracy || stat == StatName::evasion)
    {
        if(val < 0)
            coef = 3.f/(3-val);
        else
            coef = (3+val)/3.f;
    }
    else{
        if(val < 0)
            coef = 2.f/(2-val);
        else
            coef = (2+val)/2.f;
    }
    
    return (int)(coef * baseStat);
}



std::vector<StatsChanger> StatsChanger::getStatChangerAsVector() const {
    std::vector<StatsChanger> vect;
    
    // Push each stat changed as a single statChanger
    if(m_attack != 0) vect.push_back(StatsChanger(m_targetTeam, m_attack, 0, 0, 0, 0, 0, 0));
    if(m_defense != 0) vect.push_back(StatsChanger(m_targetTeam, 0, m_defense, 0, 0, 0, 0, 0));
    if(m_specialAttack != 0) vect.push_back(StatsChanger(m_targetTeam, 0, 0, m_specialAttack, 0, 0, 0, 0));
    if(m_specialDefense != 0) vect.push_back(StatsChanger(m_targetTeam, 0, 0, 0, m_specialDefense, 0, 0, 0));
    if(m_speed != 0) vect.push_back(StatsChanger(m_targetTeam, 0, 0, 0, 0, m_speed, 0, 0));
    if(m_evasion != 0) vect.push_back(StatsChanger(m_targetTeam, 0, 0, 0, 0, 0, m_evasion, 0));
    if(m_accuracy != 0) vect.push_back(StatsChanger(m_targetTeam, 0, 0, 0, 0, 0, 0, m_accuracy));
    
    
    // Return the vector
    return vect;
}



Team StatsChanger::getTargetedTeam() const {
    return m_targetTeam;
}



void StatsChanger::setTargetedTeam(Team targetTeam) {
    m_targetTeam = targetTeam;
}



bool StatsChanger::nullChanger() const {
    return sum() == 0;
}



StatName StatsChanger::getNonNullStatName() const {

    if(m_attack != 0) return StatName::attack;
    else if(m_defense != 0) return StatName::defense;
    else if(m_specialAttack != 0) return StatName::special_attack;
    else if(m_specialDefense != 0) return StatName::special_defense;
    else if(m_speed != 0) return StatName::speed;
    else if(m_accuracy != 0) return StatName::accuracy;
    else if(m_evasion != 0) return StatName::attack;
        
    else // There is a problem
        throw std::string("The StatChanger is null and getNonNullStatName was called !");
}



bool StatsChanger::canDecreaseStat(StatName stat) const {
    int val = getStatChangerValue(stat);
    
    // Return false if it is equal to the min (-6)
    return val > -6;
}



bool StatsChanger::canIncreaseStat(StatName stat) const {
    int val = getStatChangerValue(stat);
    
    // Return false if it is equal to the max (6)
    return val < 6;
}



std::wstring StatsChanger::getValAsWString(int val) const {
    
    // Reducing stats
    if(val == -1) return L"diminue.";
    else if(val == -2) return L"diminue beaucoup.";
    else if(val > -6 && val < -2) return L"diminue énormément !";
    else if(val == -6) return L"diminue au maximum !";
    
    // Increasing stats
    else if(val == 1) return L"augmente.";
    else if(val == 2) return L"augmente beaucoup.";
    else if(val > 2 && val < 6) return L"augmente énormément !";
    else if(val == 6) return L"augmente au maximum !";
    
    
    else // Else there is a problem
        throw std::string("Val ") + toString(val) + std::string(" doesn't have a corresponding WString ");
}



std::wstring StatsChanger::getFightWString(StatName stat) const {

    if(m_attack != 0) return L"L'attaque ";
    else if(m_defense != 0) return L"La défense ";
    else if(m_specialAttack != 0) return L"L'attaque spéciale ";
    else if(m_specialDefense != 0) return L"La défense spéciale ";
    else if(m_speed != 0) return L"La vitesse ";
    else if(m_accuracy != 0) return L"La précision ";
    else if(m_evasion != 0) return L"L'esquive ";
        
    else // There is a problem
        throw std::string("The StatChanger is null and getFightWString was called !");
}



void StatsChanger::add(StatName name, int val) {
    // Get the current value
    int actualVal = getStatChangerValue(name);
    
    // Calculate the final value
    int finalVal = actualVal + val;
    
    // Set the final value
    setStatChangerValue(name, finalVal);
}



void StatsChanger::add(StatsChanger sc) {
    // Add each single stat
    add(StatName::attack, sc.getStatChangerValue(StatName::attack));
    add(StatName::defense, sc.getStatChangerValue(StatName::defense));
    add(StatName::special_attack, sc.getStatChangerValue(StatName::special_attack));
    add(StatName::special_defense, sc.getStatChangerValue(StatName::special_defense));
    add(StatName::speed, sc.getStatChangerValue(StatName::speed));
    add(StatName::accuracy, sc.getStatChangerValue(StatName::accuracy));
    add(StatName::evasion, sc.getStatChangerValue(StatName::evasion));
}



void StatsChanger::reverseTarget() {
    if(m_targetTeam == Team::allied)
        m_targetTeam = Team::ennemy;
    else
        m_targetTeam = Team::allied;
}



bool StatsChanger::isNegativeChanger() const {
    return sum() < 0;
}



bool StatsChanger::isPositiveChanger() const {
    return sum() > 0;
}



int StatsChanger::sum() const {
    return m_accuracy + m_attack + m_defense + m_evasion + m_specialAttack + m_specialDefense + m_speed;
}
