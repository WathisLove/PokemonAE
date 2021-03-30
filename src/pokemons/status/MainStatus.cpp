#include "MainStatus.hpp"
#include "../../Utilities.hpp"


MainStatus::MainStatus() :
m_name(MainStatusName::NoMainStatus),
m_turns(0){

}


MainStatus::MainStatus(MainStatusName name) :
m_name(name),
m_turns(0){
    if(name == MainStatusName::BadlyPoison)
        m_turns = 1;
    
    // If the status is sleep, then choose a number of turns between 1 and 3
    else if(name == MainStatusName::Sleep)
        m_turns = randomInt(1, 3);
    
}



MainStatus::MainStatus(MainStatusName name, int turns) :
m_name(name),
m_turns(turns){
    if(name == MainStatusName::BadlyPoison)
        m_turns = 1;
}



MainStatusName MainStatus::getName() const {
    return m_name;
}



int MainStatus::getTurns() const {
    return m_turns;
}



void MainStatus::updateTurns() {
    if(m_name == MainStatusName::BadlyPoison)
        m_turns += 1;
    else if(m_name == MainStatusName::Sleep)
        m_turns -= 1;
}



void MainStatus::changeStatus(MainStatusName name) {
    m_name = name;
    
    if(name == MainStatusName::BadlyPoison)
        m_turns = 1;
    else
        m_turns = 0;
}



void MainStatus::changeStatus(MainStatusName name, int turns) {
    m_name = name; 
    
    if(name == MainStatusName::BadlyPoison)
        m_turns = 1;
    else
        m_turns = turns;
}



void MainStatus::clearStatus() {
    m_name = MainStatusName::NoMainStatus;
    m_turns = 0;
}



bool MainStatus::statusEnd() const{
    if(m_name == MainStatusName::Sleep)
        return m_turns == 0;
    else if(m_name == MainStatusName::Freeze)
        return randomInt(1,5) == 1;
    
    else
        return false;
}



float MainStatus::getDamageFactor() const {
    // If Normally poisoned
    if(m_name==MainStatusName::Poison || m_name == MainStatusName::Burn)
        return 1.f/8;
    
    // If Badly poisoned
    else if(m_name==MainStatusName::BadlyPoison)
        return m_turns/16.f;
    
    else
        return 0;
}



bool MainStatus::isPoison() const {
    return m_name == MainStatusName::Poison || m_name == MainStatusName::BadlyPoison; 
}



std::string MainStatus::toString() const {
    if(m_name == MainStatusName::BadlyPoison || m_name == MainStatusName::Poison)
        return std::string("poison");
    else if(m_name == MainStatusName::Burn)
        return std::string("burn");
    else if(m_name == MainStatusName::Freeze)
        return std::string("freeze");
    else if(m_name == MainStatusName::Paralysis)
        return std::string("paralysis");
    else if(m_name == MainStatusName::Sleep)
        return std::string("sleep");
    
    else 
        return std::string("");
}



float MainStatus::getCaptureBonus() {
    if(m_name == MainStatusName::Sleep || m_name == MainStatusName::Freeze)
        return 2.;
    else if(m_name == MainStatusName::NoMainStatus)
        return 1.;
    else
        return 1.5;
}
