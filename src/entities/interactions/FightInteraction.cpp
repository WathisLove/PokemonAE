#include "FightInteraction.hpp"
#include "Interaction.hpp"
#include "../../states/GameState.hpp"

#include <cassert>
#include <iostream>

FightInteraction::FightInteraction(NpcID npc, int interactionNumber) :
Interaction(npc, interactionNumber){
    
}



void FightInteraction::handleGameEvent(const GameEvent& event) {
    if(event.getType() == EventType::StatePopped && (event.stateID == StateID::TrainerFightS || event.stateID == StateID::WildFightS)){
        m_isFinished = true;
        std::cout << "Fight Finished" << std::endl;
    }
}



void FightInteraction::startInteraction(StateStack* stack, Entity* e) const {
    assert(e!= nullptr && e->getType() == EntityType::Trainer_Type);
    
    // Convert to a trainer
    Trainer* t = (Trainer*)e;
    
    if(!t->isDefeated()){
        GameState* gs = (GameState*)stack->getStateOfID(StateID::GameS);
        stack->requestStackPushFight(gs->getCharacter(), e);
    }
    else{
        // Simulate the Fight Ended
        GameEvent* event = new GameEvent(EventType::StatePopped);
        event->stateID = StateID::TrainerFightS;
        stack->addGameEvent(event);
    }
}
