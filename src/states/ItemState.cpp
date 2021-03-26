#include "ItemState.hpp"
#include "../Constants.hpp"
#include "../zones/Zone.hpp"
#include <iostream>

ItemState::ItemState(StateStack* stack, Character* character, ItemID item, int number) :
DialogState(stack, character, new sf::String()){
    
    m_id = StateID::ItemS;
    
    // Give the item to the character
    character->giveItem(item, number);
    
    // Setup the ItemDisplay  
    m_item = new Item(item);
    m_itemDisplayed = new ItemDisplay(stack->getContext(), m_item);
    m_itemDisplayed->setOrigin(sf::Vector2f(16,16));
    m_itemDisplayed->setZoomFactor(GAME_ZOOM);
    m_itemDisplayed->setPosition(stack->getContext().getWindowCenter());
    
    
    // Change the BackgroundTexture
    m_uiSprite.setTexture(m_stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_itemGift));
    
    
    // Set the Dialog String
    if(m_item->getCategory() == ItemCategory::CT){
        // CT Dialog
        m_string = new sf::String("Vous obtenez la " + Item::getName(item));
    }
    else{
        // Other item dialog
        m_string = new sf::String("Vous obtenez " + toString(number) + " " + Item::getName(item));
    }
    setDialogString();
}



void ItemState::draw() {
    DialogState::draw();
    
    // Draw the ItemDisplay
    m_stack->getContext().getRenderWindow().draw(*m_itemDisplayed);
}



ItemState::~ItemState() {
    m_character->getZone()->deleteDeadEntities();
    
    // Delete the Item
    delete m_item;
}
