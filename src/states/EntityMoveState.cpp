#include "EntityMoveState.hpp"

#include "../entities/Entity.hpp"
#include "../entities/movements/EntityMover.hpp"
#include "../utility/Logger.hpp"


EntityMoveState::EntityMoveState(StateStack* stack, Entity* entity, EntityMover* mover) :
State(stack),
m_movingEntity(entity),
m_mover(mover)
{
    // Set the State ID
    m_id = StateID::EntityMoveS;
    
    // Set the Entity Mover
    entity->setMover(mover);
}



void EntityMoveState::draw() {
    // Nothing to draw
}



bool EntityMoveState::handleEvent(sf::Event& event) {
    return false;
}



void EntityMoveState::actionOnCompletion() {
    m_stack->requestStackPop();
    
    // Reset the mover of the Entity
    // Old mover is deleted
    m_movingEntity->clearMover();
}



bool EntityMoveState::update(float dt) {
    // Update Entity
    m_movingEntity->update(dt);
    
    // If mover finished -> complete and set NoMover
    if(m_mover->isFinished()){
        Log("Finished Movements !");
        m_isCompleted = true;
    }
    
    return false;
}
