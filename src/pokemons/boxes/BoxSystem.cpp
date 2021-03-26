#include "BoxSystem.hpp"

BoxSystem::BoxSystem() {
    // By default create an empty box
    addEmptyBox();
}



BoxSystem::~BoxSystem() {
    // Delete each box
    for(PokemonBox* b : m_boxes)
        delete b;
}



PokemonBox* BoxSystem::getBox(int index) {
    return m_boxes.at(index);
}



void BoxSystem::addPokemon(Pokemon* pokemon) {
    bool placed = false;
    
    // We check each box for remaining place
    for(PokemonBox* b : m_boxes){
        // If there is place in the box
        if(b->hasPlace()){
            // Add the pokemon and leave the loop
            b->addPokemon(pokemon);
            placed = true;
            break;
        }
    }
    
    // Otherwise we add a new box for the pokemon
    if(!placed)
        addBox(pokemon);
    
    // If there is a pokemon in the last box, adds an other empty box
    if(!m_boxes.at(m_boxes.size()-1)->isEmpty()){
        addEmptyBox();
    }
}



int BoxSystem::addPokemon(Pokemon* pokemon, int boxNumber, int boxIndex) {
    // Int for the final res
    int res;
    
    // Get the box
    PokemonBox* b = m_boxes.at(boxNumber);
    
    // If there is place in the box
    if(b->hasPlace()){
        b->addPokemon(pokemon, boxIndex);
        res = boxNumber;
    }
    else{
        // Else we go through all the boxes
        for(int i = 0; i < m_boxes.size(); i++){ 
            // Get the box i
            PokemonBox* b = m_boxes.at(i);

            // If there is place in the box
            if(b->hasPlace()){
                b->addPokemon(pokemon, boxIndex);
                res = i;
                
                // Quit
                i = m_boxes.size();
            }
        }
    }
    
    // If there is a pokemon in the last box, adds an other empty box
    if(!m_boxes.at(m_boxes.size()-1)->isEmpty()){
        addEmptyBox();
    }
    
    // Return the box in which a pokemon was added
    return res;
}



int BoxSystem::size() {
    return m_boxes.size();
}



void BoxSystem::addEmptyBox() {
    PokemonBox* box = new PokemonBox();
    box->setName(L"Boite " + toWString(m_boxes.size()+1));
    
    m_boxes.push_back(box);
}



void BoxSystem::addBox(Pokemon* pokemon) {
    PokemonBox* box = new PokemonBox();
    box->addPokemon(pokemon);
    box->setName(L"Boite " + toWString(m_boxes.size()+1));
    
    m_boxes.push_back(box);
}
