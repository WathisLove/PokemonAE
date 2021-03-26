#include "FightStage.hpp"

#include <iostream>

FightStage::FightStage(FightStageName name, QuitCondition quitCondition) :
m_name(name),
m_quitCondition(quitCondition),
m_lifeTime(0),
m_startAction(nullptr),
m_updateAction(nullptr),
m_quitAction(nullptr){
    if((int)name > 100)
        std::cout << "building a state with ID " << (int)name << std::endl; 
}



FightStageName FightStage::getName() const{
    return m_name;
}



QuitCondition FightStage::getQuitCondition() const {
    return m_quitCondition;
}



action FightStage::onStartAction() const{
    return m_startAction;
}



action FightStage::onUpdateAction() const{
    return m_updateAction;
}



action FightStage::onQuitAction() const{
    return m_quitAction;
}



void FightStage::setQuitAction(action quitAction) {
    m_quitAction = quitAction;
}



void FightStage::setUpdateAction(action updateAction) {
    m_updateAction = updateAction;
}


void FightStage::setStartAction(action startAction) {
    m_startAction = startAction;
}



float FightStage::getLifeTime() const{
    return m_lifeTime;
}



void FightStage::setLifeTime(float time) {
    m_lifeTime = time;
}
