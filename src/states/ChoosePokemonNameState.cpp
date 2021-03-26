#include "ChoosePokemonNameState.hpp"



ChoosePokemonNameState::ChoosePokemonNameState(StateStack* stack, Pokemon* pokemon) :
ChooseNameState(stack),
m_pokemon(pokemon)
{
    ChooseNameState::displayPokemon(pokemon->getID());
}



void ChoosePokemonNameState::actionOnCompletion() {
    // Call inherited method
    ChooseNameState::actionOnCompletion();
    
    // Rename the pokemon
    m_pokemon->setName(getEnteredString());
}
