#include "SellerActionState.hpp"

SellerActionState::SellerActionState(StateStack* stack, Character* character, Seller* seller) :
ChoiceState(stack, character, new sf::String("Bienvenue !")),
m_seller(seller){
    // Set the Satte ID
    m_id = StateID::SellerActionS;
    
    // Set the Entries
    m_menu.clearEntries();
    m_menu.addEntry(L"Acheter");
    m_menu.addEntry(L"Vendre");
    m_menu.addEntry(L"Annuler");
}



void SellerActionState::actionOnCompletion() {
    // Pop this State
    m_stack->requestStackPop();
    
    // Get the Menu Entry
    int entrySelected = m_menu.getSelectedEntry();
    
    // Push a Seller State
    if(entrySelected == 0)
        m_stack->requestStackPush(StateID::SellerS, m_character, m_seller);
    // Push a Buying State
    else if(entrySelected == 1)
        m_stack->requestStackPush(StateID::BuyingS, m_character, m_seller);
    // Push an End dialog
    else{
        m_stack->requestStackPushDialog(sf::String(L"Au revoir !"));
    }
}



bool SellerActionState::update(float dt) {
    return false;
}



bool SellerActionState::handleEvent(sf::Event& event) {
    // Get the key if one was pressed
    if(event.type == sf::Event::KeyPressed){
        // Get the Key
        sf::Keyboard::Key key = getKeyPressed(event);
        
        // Close if Escape is pressed
        if(key == sf::Keyboard::Escape){
            m_menu.selectLastEntry();
            m_isCompleted = true;
        }
        // Let the Choice State manage the other events
        else
            ChoiceState::handleEvent(event);
    }

    return false;
}
