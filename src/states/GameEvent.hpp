#ifndef GAMEEVENT_HPP
#define GAMEEVENT_HPP

#include <SFML/System/String.hpp>

#include "StateID.hpp"

class Entity;
class Attack;

//=================// Enum //==================//
    
enum class EventType{
    NameChosen,
    PokemonSelected,
    ChoiceSelected,
    RequestStateClosure,
    StatePopped,
    RequestInteraction,
    InteractionsFinished, // Sequence of interaction finished
    FightWon,
    FightLost,
    ZoneLoaded,
    SelectingAttack
};
    
    
           
class GameEvent {
public:

//=================// Methods //==================//
    
    /**
     * Constructor
     */
    GameEvent(EventType type);

    /**
     * Destructor
     */
    virtual ~GameEvent();    
    
    
    /**
     * Get the GameEvent type
     * @return 
     */
    EventType getType() const;
    
    
//=================// Class Attributes //==================//
    
public:
    // The data linked to the GameEvent
    union {
        sf::String* string;
        bool confirm;
        StateID stateID;
        Entity* entity;
        int choice;
        Attack* attack;
    };
    
private:
    // The Event Type
    EventType m_type;
};

#endif /* GAMEEVENT_HPP */

