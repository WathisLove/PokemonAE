#include "UIPokedexState.hpp"
#include "../../resources/FontHolder.hpp"

#include <iostream>

UIPokedexState::UIPokedexState(Context& context, Pokedex& pokedex) :
m_context(context),
m_pokedex(pokedex),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_pokedexBackground)),
m_entryCursor(context.getTextureHolder()->getTexture(TextureHolder::ui_pokedexCursor)),
m_showList(true),
m_description("", m_context.getFontHolder()->getFont(FontHolder::dialogFont)),
m_totalCaptured("", m_context.getFontHolder()->getFont(FontHolder::dialogFont)),
m_totalSeen("", m_context.getFontHolder()->getFont(FontHolder::dialogFont)),
m_currentInfos(context){
    // Create the Entries
    createEntries();
    
    setupTexts();
}



UIPokedexState::~UIPokedexState() {
    // Delete the Entries
    // Draw all the Entries
    for(PokedexEntry* entry : m_entries){
        delete entry;
    }
}



void UIPokedexState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    target.draw(m_background, states);
    target.draw(m_currentInfos, states);
    target.draw(m_totalSeen, states);
    target.draw(m_totalCaptured, states);
    
    // Draw the list or the description
    if(m_showList){
        target.draw(m_entryCursor, states);

        // Draw all the Entries
        for(PokedexEntry* entry : m_entries){
            target.draw(*entry, states);
        }
    }
    else{
        target.draw(m_description, states);
    }
}



void UIPokedexState::selectEntry(int number) {
    // Top left position
    sf::Vector2f topLeft = m_background.getPosition();
    
    // The number of entries before going down
    int fixEntries = 5;
    
    // Just the cursor for the first entries
    if(number < fixEntries){
        setEntriesPositions(topLeft + sf::Vector2f(400, 40));
        
        m_entryCursor.setPosition(topLeft + sf::Vector2f(398, 38 + 40 * (number)));
    }
    // Just the cursor for the last entries
    else if(number > ((int)m_entries.size() - fixEntries)){
        setEntriesPositions(topLeft + sf::Vector2f(400, 40 * (2 * fixEntries - (int)m_entries.size())));

        m_entryCursor.setPosition(topLeft + sf::Vector2f(398, 38 + 40 * (2 + number - fixEntries)));
    }
    // Else move the entries
    else{
        setEntriesPositions(topLeft + sf::Vector2f(400, 40 * (fixEntries - number)));
        
        m_entryCursor.setPosition(topLeft + sf::Vector2f(398, 38 + 40 * (fixEntries-1)));
    }
    
    // Get the Pokemon ID
    PokemonID id = (PokemonID)number;
    
    // Check if he was captured or seen
    int captured = m_pokedex.getNumberCaptured(id);
    int seen = m_pokedex.getNumberSaw(id);
    
    // Update the Infos if needed
    m_currentInfos.setPokemon(id, captured, seen);
    
    
    updateDescription(id);
}



void UIPokedexState::showInfos() {
    m_showList = false;
}



void UIPokedexState::showList() {
    m_showList = true;
}



void UIPokedexState::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    m_currentInfos.setPosition(pos);
    
    m_totalCaptured.setPosition(pos + sf::Vector2f(120, 500));
    m_totalSeen.setPosition(pos + sf::Vector2f(60, 500));
    m_description.setPosition(pos + sf::Vector2f(400, 450));
    
    setEntriesPositions(pos + sf::Vector2f(400, 40));
}



void UIPokedexState::createEntries() {
    // Get the Pokemon saw
    std::vector<PokemonID>* list(m_pokedex.getAllPokemons());
    
    // Create entries for each pokemon in the pokedex
    for(PokemonID id : *list){
        PokedexEntry* entry = new PokedexEntry(m_context, id);
        
        // Set the Entry to saw, captured or unknown
        if(m_pokedex.captured(id))
            entry->setCaptured();
        else if(m_pokedex.saw(id))
            entry->setSaw();
        else
            entry->setUnknown();
        
        m_entries.push_back(entry);
    }

    
    // Delete the set
    delete list;
}



void UIPokedexState::setEntriesPositions(sf::Vector2f firstPosition) {
    // Set the positions of the Entries
    // Draw all the Entries
    for(int i = 0; i < m_entries.size(); i++){
        PokedexEntry* entry = m_entries.at(i);
        entry->setPosition(firstPosition + sf::Vector2f(0, i*40));
    }
}



void UIPokedexState::updateDescription(PokemonID id) {
    if(m_pokedex.captured(id)){
        m_description.setString("Description pas implémentée /!\\");
    }
    else{
        m_description.setString("Description indisponible");
    }
}



void UIPokedexState::setupTexts() {
    // Colors
    m_description.setFillColor(sf::Color::Black);
    m_totalCaptured.setFillColor(sf::Color::Black);
    m_totalSeen.setFillColor(sf::Color::Black);
    
    
    // Set the total seen and captured
    m_totalCaptured.setString(toString(m_pokedex.getTotalCaptured()));
    m_totalSeen.setString(toString(m_pokedex.getTotalSaw()));
}
