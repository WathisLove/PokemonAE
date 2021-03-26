#include <cassert>
#include <iostream>

#include "SellerState.hpp"

SellerState::SellerState(StateStack* stack, Character* character, Seller* seller) :
State(stack),
m_ui(stack->getContext(), seller, character->getMoney()),
m_character(character),
m_seller(seller),
m_currentEntry(0),
m_quantity(1){
    
    // Set the State ID
    m_id = StateID::SellerS;
    
    // Set the UI position
    m_ui.setPosition(m_stack->getContext().getWindowTopLeftCorner());
    
    // Select the first entry
    m_ui.setCurrentEntry(0);
}



void SellerState::actionOnCompletion() {
    m_stack->requestStackPop();
    
    // Push a Seller Choice State
    m_stack->requestStackPush(StateID::SellerActionS, m_character, m_seller);
}



bool SellerState::isCompleted() const {
    return m_isCompleted;
}



void SellerState::draw() {
    // Get a reference to the window and draw the UI
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_ui);
}



bool SellerState::handleEvent(sf::Event& event) {
    
    // Check if we pressed a key
    if(event.type == sf::Event::KeyPressed){
        // Get the key
        sf::Keyboard::Key key = event.key.code;
        
        // If we are note buying
        if(!m_isBuying){
            // Close the SellerState if Escape is pressed
            if(key == sf::Keyboard::Escape)
                m_isCompleted = true;
            // Select the Next entry
            else if(key == sf::Keyboard::S)
                next();
            // Select the Previous entry
            else if(key == sf::Keyboard::Z)
                previous();
            // Select the Previous entry
            else if(key == sf::Keyboard::Space)
                select();
        }
        else{
            // Close the SellerState if Escape is pressed
            if(key == sf::Keyboard::Escape)
                unselect();
            // Select the Next entry
            else if(key == sf::Keyboard::D)
                increase();
            // Select the Previous entry
            else if(key == sf::Keyboard::Q)
                decrease();
            // Select the Previous entry
            else if(key == sf::Keyboard::Space)
                buy();
        }
    }
    
    return false;
}



bool SellerState::update(float dt) {
    
    
    return false;
}



void SellerState::next() {
    // Increase the current entry
    m_currentEntry = (m_currentEntry + 1) % m_seller->getNbItems();
    
    // Set the UI current Entry
    m_ui.setCurrentEntry(m_currentEntry);
}



void SellerState::previous() {
    // Get the number of entries
    int entryNumber = m_seller->getNbItems();
    
    // Increase the current entry
    m_currentEntry = (m_currentEntry + entryNumber - 1) % entryNumber;
    
    // Set the UI current Entry
    m_ui.setCurrentEntry(m_currentEntry);
}



void SellerState::select() {
    
    // Get the item price
    int price = m_seller->getItemPrice(m_currentEntry);
    
    
    // Select if we have enough money for one
    if(m_character->getMoney() >= price){
        m_isBuying = true;

        // Set the UI to selected
        m_ui.setSelected(true);

        // Set the quantity
        m_quantity = 1;

        m_ui.setQuantity(m_quantity, price);
    }
    else{
        // Show a dialog as we don't have enough money
        m_stack->requestStackPushDialog(sf::String(L"Vous n'avez pas assez d'argent pour ça."));
    }
}



void SellerState::unselect() {
    m_isBuying = false;
    m_quantity = 1;
    
    m_ui.setSelected(false);
}



void SellerState::increase(int number) {
    // Get the price of the item
    int price = m_seller->getItemPrice(m_currentEntry);
    assert(price != 0);
    
    // Calculate the maximum quantity
    int maxQuantity = (int)(m_character->getMoney() / price) + 1;
    
    // Calculate the maximum quantity
    m_quantity = (m_quantity + number) % maxQuantity;
    
    // Set the minimum to 1
    if(m_quantity == 0 && m_character->getMoney() >= price)
        m_quantity = 1;
    
    // Update the UI
    m_ui.setQuantity(m_quantity, m_quantity*price);
}



void SellerState::decrease(int number) {
    // Get the price of the item
    int price = m_seller->getItemPrice(m_currentEntry);
    assert(price != 0);
    
    // Calculate the maximum quantity
    int maxQuantity = (int)(m_character->getMoney() / price) + 1;
    
    // Calculate the maximum quantity
    m_quantity = (m_quantity + maxQuantity - number) % maxQuantity;
    
    // Go back to the max if we reached 0
    if(m_quantity == 0 && m_character->getMoney() >= price)
        m_quantity = maxQuantity-1;
    
    // Update the UI
    m_ui.setQuantity(m_quantity, m_quantity*price);
}



void SellerState::buy() {
    std::cout << "Buying !" << std::endl;
    
    // Get the price of the item
    int price = m_seller->getItemPrice(m_currentEntry);
    
    
    // Get the product ID
    ItemID productID = m_seller->getItemiD(m_currentEntry);

    // Dialog
    m_stack->requestStackPushDialog(sf::String(L"Vous achetez ") + toString(m_quantity) + L" "
                                    + Item::getName(productID) + L".");


    // Pay money
    m_character->pay(price * m_quantity);

    // Add the item to the Character inventory
    m_character->giveItem(productID, m_quantity);
    
    
    // Reset the UI 
    m_ui.setCharacterMoney(m_character->getMoney());
    
    // Unselect the entry
    unselect();
}
