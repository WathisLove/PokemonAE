#include "UIBoxState.hpp"
#include "../../resources/FontHolder.hpp"

#include <iostream>

UIBoxState::UIBoxState(Context& context, Character* character) :
m_context(context),
m_character(character),
m_boxes(character->getBoxSystem()),
m_menu(context),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_boxBackground)),
m_cursor(context.getTextureHolder()->getTexture(TextureHolder::ui_boxCursor)),
m_titleCursor(context.getTextureHolder()->getTexture(TextureHolder::ui_boxTitleCursor)),
m_boxTitle("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_showCursor(true),
m_showTitleCursor(false){
    
    // Setup
    setupPokemonDisplays();
    setInTeamEntries();
    
    // Set team
    setTeam(*(m_character->getPokemonTeam()));
    
    // Show the first box
    setBox(0);
    
    m_boxTitle.setFillColor(sf::Color::Black);
}



void UIBoxState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    target.draw(m_menu, states);
    target.draw(m_boxTitle, states);
    
    
    // Draw the team pokemons
    for(PokemonMiniDisplay* disp : m_teamDisplays)
        disp->draw(target, states);
    // Draw the box pokemons
    for(PokemonMiniDisplay* disp : m_boxDisplays)
        disp->draw(target, states);
    
    if(m_showCursor)
        target.draw(m_cursor, states);
    if(m_showTitleCursor)
        target.draw(m_titleCursor, states);
    
    // Draw the selected pokemon if needed
    m_selectedPokemon->draw(target, states);
}



bool UIBoxState::isMenuOpen() {
    return m_menu.isOpen();
}



void UIBoxState::setBox(int boxNumber) {
    // Get the box
    PokemonBox* box = m_boxes.getBox(boxNumber);
    
    // Set the box displays
    for(int i = 0; i < m_boxDisplays.size(); i++){
        // Get the display
        PokemonMiniDisplay* display = m_boxDisplays.at(i);
        
        // Check if there is a pokemon
        Pokemon* p = box->getPokemonAt(i);
        
        if(p != nullptr){
            display->setPokemon(p->getID());
            display->show();
        }
        else{
            display->hide();
        }
    }
    
    // Set the box Title
    m_boxTitle.setString(box->getName());
}



void UIBoxState::setPosition(sf::Vector2f pos) {
    
    // Set the background position
    m_background.setPosition(pos);
    
    m_menu.setPosition(pos + sf::Vector2f(500, 480));
    
    // The box and team offsets
    sf::Vector2f boxOffset(100, 50);
    sf::Vector2f teamOffset(4, 10);
    
    // Set their positions
    setBoxPosition(pos + boxOffset);
    setTeamPosition(pos + teamOffset);
    
    // Set the cursor position
    setCursorPosition(0, true);
    
    // Set the Title position
    m_boxTitle.setPosition(pos + sf::Vector2f(224, 15));
    m_titleCursor.setPosition(pos + sf::Vector2f(116, 2));
}



void UIBoxState::selectPokemon(PokemonID id) {    
    m_selectedPokemon->setPokemon(id);
    m_selectedPokemon->show();
}



void UIBoxState::unselectPokemon() {
    m_selectedPokemon->hide();
}



void UIBoxState::setCursorPosition(int pos, bool inTeam) {
    
    // The UI top left positon
    sf::Vector2f topPos = m_background.getPosition();
    sf::Vector2f offset(0,0);
    
    // Set the cursor position in team
    if(inTeam){
        offset.x = 2;
        offset.y = 7 + 40 * pos;
    }
    // Set the cursor position in box
    else{
        offset.x = 98 + 40 * (pos%6);
        offset.y = 48 + 40 * (pos/6);
    }
    
    // Cursor position
    m_cursor.setPosition(topPos + offset);
    
    
    if(m_showTitleCursor){
        // Move the pokemon over the box title
        m_selectedPokemon->setPosition(topPos + sf::Vector2f(208, 5));
    }
    else{
        // Selected pokemon position
        m_selectedPokemon->setPosition(topPos + offset + sf::Vector2f(4, -8));
    }
    
    
    // If the cursor is in the team
    if(inTeam)
        setInTeamEntries();
    else
        setInBoxEntries();
}



void UIBoxState::showMenu(bool show) {
    if(show)
        m_menu.open();
    else
        m_menu.close();
}



void UIBoxState::showCursor(bool show) {
    m_showCursor = show;
}



void UIBoxState::showTitleCursor(bool show) {
    m_showTitleCursor = show;
}



ChoiceMenu& UIBoxState::getMenu() {
    return m_menu;
}



void UIBoxState::setBoxPosition(sf::Vector2f offset) {
    for(int i = 0; i < m_boxDisplays.size(); i++){
        sf::Vector2f displayPos;
        
        displayPos.x = 40 * (i%6);
        displayPos.y = 40 * (i/6);
        
        m_boxDisplays.at(i)->setPosition(offset + displayPos);
    }
}



void UIBoxState::setTeamPosition(sf::Vector2f offset) {
    for(int i = 0; i < m_teamDisplays.size(); i++){
        sf::Vector2f displayPos;
        
        displayPos.x = 0;
        displayPos.y = 40 * (i%6);
        
        m_teamDisplays.at(i)->setPosition(offset + displayPos);
    }
}



void UIBoxState::setTeam(PokemonTeam& team) {
    for(int i = 0; i < team.getNbPokemon(); i++){
        // Set the display for each pokemon
        m_teamDisplays.at(i)->setPokemon(team.getPokemonAt(i)->getID());
        m_teamDisplays.at(i)->show();
    }
    // Hide the other displays
    for(int i = team.getNbPokemon(); i < m_teamDisplays.size(); i++){
        m_teamDisplays.at(i)->hide();
    }
}



void UIBoxState::setupPokemonDisplays() {

    // Create selected pokemon display
    m_selectedPokemon = new PokemonMiniDisplay(m_context);
    m_selectedPokemon->hide();
    
    // Create box displays
    for(int i = 0; i < m_boxDisplays.size(); i++){
        PokemonMiniDisplay* display = new PokemonMiniDisplay(m_context);
        display->hide();
        m_boxDisplays.at(i) = display;
    }
    
    // Create team displays
    for(int i = 0; i < m_teamDisplays.size(); i++){
        PokemonMiniDisplay* display = new PokemonMiniDisplay(m_context);
        display->hide();
        m_teamDisplays.at(i) = display;
    }
}



void UIBoxState::setInTeamEntries() {
    m_menu.clearEntries();
    
    m_menu.addEntry(L"Déplacer");
    m_menu.addEntry(L"Déposer");
    m_menu.addEntry(L"Résumé");
    m_menu.addEntry(L"Annuler");
}



void UIBoxState::setInBoxEntries() {
    m_menu.clearEntries();
    
    m_menu.addEntry(L"Déplacer");
    m_menu.addEntry(L"Retirer");
    m_menu.addEntry(L"Résumé");
    m_menu.addEntry(L"Annuler");
}
