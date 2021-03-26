#include "BuyingState.hpp"
#include <iostream>


BuyingState::BuyingState(StateStack* stack, Character* character, Seller* seller) :
State(stack),
m_character(character),
m_bagState(nullptr),
m_seller(seller),
m_ui(stack->getContext()),
m_currentQuantity(0),
m_maxQuantity(0),
m_isChoosingQuantity(false)
{
    // Set the State ID
    m_id = StateID::BuyingS;
    
    // Set the UI Position
    m_ui.setPosition(m_stack->getContext().getWindowTopLeftCorner());
}



void BuyingState::actionOnCompletion() {
    m_stack->requestStackPop();
    
    // Push a Seller Choice State
    m_stack->requestStackPush(StateID::SellerActionS, m_character, m_seller);
}



void BuyingState::draw() {
    // Draw the Buying UI if an item is chosen
    if(m_isChoosingQuantity){
        sf::RenderWindow& window = getRenderWindow();
        
        // Draw the UI
        window.draw(m_ui);
    }
}



bool BuyingState::handleEvent(sf::Event& event) {
    // Get the key if one was pressed
    if(event.type == sf::Event::KeyPressed){
        // Get the Key
        sf::Keyboard::Key key = getKeyPressed(event);
        
        // If we are choosing the item quantity
        if(m_isChoosingQuantity){
            if(key == sf::Keyboard::Escape)
                unselect();
            else if(key == sf::Keyboard::Space)
                confirmQuantity();
            else if(key == sf::Keyboard::D)
                increase();
            else if(key == sf::Keyboard::Q)
                decrease();
        }
        else{
            if(key == sf::Keyboard::Escape){
                m_isCompleted = true;
                closeBag();
            }
        }
    }
    
    // Prevent bottom states from handling events
    return false;
}



bool BuyingState::isCompleted() const {
    return m_isCompleted;
}



bool BuyingState::update(float dt) {
    if(m_bagState != nullptr){
        // If an Item was selected
        if(!m_isChoosingQuantity){
            if(m_bagState->hasSelectedItem()){
                select();
            }
        }
    }
    else{
        // Try to find the bag State
        findBagState();
    }
    
    // Prevent bottom states from updating
    return false;
}



void BuyingState::openBag() {
    // Open a Bagstate
    m_stack->requestStackPush(StateID::BagS, m_character);
}



void BuyingState::closeBag() {
    // Close the BagState
    m_bagState->waitBeforeClosing(false);
    m_bagState->actionOnCompletion();
}



void BuyingState::findBagState() {
    // Try to find a BagState
    if(m_stack->hasStateOfID(StateID::BagS)){
        // Get tha 
        m_bagState = (BagState*)m_stack->getStateOfID(StateID::BagS);
        
        m_bagState->setAsSecondaryState(true);
        m_bagState->deactivateMenu();
        m_bagState->letEventPass(true);
    }
    else{
        // Open a bag state as there is none
        openBag();
    }
}



void BuyingState::increase() {
    m_currentQuantity = 1 + (m_currentQuantity % m_maxQuantity);
    
    // Update the UI
    m_ui.setItemSold(m_currentQuantity, m_maxQuantity);
}



void BuyingState::decrease() {
    m_currentQuantity = (m_currentQuantity + m_maxQuantity - 1) % m_maxQuantity;
    
    // Cycle to the max
    if(m_currentQuantity == 0)
        m_currentQuantity = m_maxQuantity;
    
    // Update the UI
    m_ui.setItemSold(m_currentQuantity, m_maxQuantity);
}



void BuyingState::select() {
    m_isChoosingQuantity = true;
    
    // Get the item quantities
    ItemID id = m_bagState->getItemIDSelected();
    
    // Get the quantity in the character inventory
    m_currentQuantity = 1;
    m_maxQuantity = m_character->getInventory()->getItemCount(id);
    
    // Update the UI
    m_ui.setItem(id);
    m_ui.setItemSold(m_currentQuantity, m_maxQuantity);
    
    
    // Hide the BagState
    m_bagState->show(false);
    m_bagState->ignoreEvents(true);
}



void BuyingState::confirmQuantity() {
    // Get the Item
    ItemID item = m_bagState->getItemIDSelected();
    
    // Sell the item
    int price = m_seller->getBuyingPrice(item);
    m_character->addMoney(m_currentQuantity * price);
    
    // Remove the items from the inventory
    m_character->getInventory()->removeItems(item, m_currentQuantity);
    
    // Update the BagState
    m_bagState->updateItemList();
    
    // Unselect the item in the bag
    unselect();
}



void BuyingState::unselect() {
    m_isChoosingQuantity = false;
    
    // Unselect the item in the BagState
    m_bagState->unselectItem();
    
    
    // Hide the BagState
    m_bagState->show(true);
    m_bagState->ignoreEvents(false);
}