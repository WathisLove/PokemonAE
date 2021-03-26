/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChoosePokemonNameState.hpp
 * Author: Redbuzard
 *
 * Created on 7 septembre 2020, 13:16
 */

#ifndef CHOOSEPOKEMONNAMESTATE_HPP
#define CHOOSEPOKEMONNAMESTATE_HPP

#include "StateStack.hpp"
#include "../pokemons/Pokemon.hpp"
#include "ChooseNameState.hpp"

class ChoosePokemonNameState : public ChooseNameState{
public:
//=================// Constructor //==================//
    
    ChoosePokemonNameState(StateStack* stack, Pokemon* pokemon);
    
    
//=================// Inherited methods //==================//
    
    /**
     * Act when the State is completed 
     * As we are in a DialogState we wait until a state request our result
     */
    virtual void actionOnCompletion() override;
    
    
private:
//=================// Attributes //==================//

    // The pokemon we want to name
    Pokemon* m_pokemon;
};

#endif /* CHOOSEPOKEMONNAMESTATE_HPP */

