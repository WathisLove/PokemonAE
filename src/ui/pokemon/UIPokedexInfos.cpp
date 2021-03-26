#include "UIPokedexInfos.hpp"
#include "../../resources/FontHolder.hpp"


UIPokedexInfos::UIPokedexInfos(Context& context) :
m_context(context),
m_pokemonDisplay(context, PokemonID::marcacrin, Team::ennemy),
m_type1(context, Type::None),
m_type2(context, Type::None)
{
    setupTexts();
    
    m_pokemonDisplay.setZoomFactor(2.5);
}



void UIPokedexInfos::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_pokemonDisplay, states);
    target.draw(m_number, states);
    target.draw(m_name, states);
    target.draw(m_seen, states);
    target.draw(m_captured, states);
    target.draw(m_type1, states);
    target.draw(m_type2, states);
}



void UIPokedexInfos::setPosition(sf::Vector2f pos) {
    m_number.setPosition(pos + sf::Vector2f(30, 30));
    m_pokemonDisplay.setPosition(pos + sf::Vector2f(50, 40));
    m_type1.setPosition(pos + sf::Vector2f(40, 270));
    m_type2.setPosition(pos + sf::Vector2f(100, 270));
    m_seen.setPosition(pos + sf::Vector2f(40, 340));
    m_captured.setPosition(pos + sf::Vector2f(80, 340));
}



void UIPokedexInfos::setPokemon(PokemonID id, int captured, int saw) {
    // Create a pokemon with the ID
    Pokemon* p = new Pokemon(id, 1);
    
    // Set the Number
    m_number.setString(toString((int)(id+1)));
    
    // Set the numbers seen and captured
    m_captured.setString(toString(captured));
    m_seen.setString(toString(saw));
    
    if(saw > 0){
        // Set the Display
        m_pokemonDisplay.display(true);
        m_pokemonDisplay.setPokemonTexture(m_context, p);
    
        // Set the Texts
        m_name.setString(p->getName());
        
        if(captured > 0){
            // Set the Type Displays
            m_type1.setType(p->getType().getFirstType());
            m_type2.setType(p->getType().getSecondType());
        }
        else{
            // Set the Type Displays
            m_type1.setType(Type::None);
            m_type2.setType(Type::None);
        }
    }
    else{
        // Hide the Display
        m_pokemonDisplay.display(false);
        
        // Set the description and name
        m_name.setString("???");
        
        // Set the Type Displays
        m_type1.setType(Type::None);
        m_type2.setType(Type::None);
    }
    
    // Delete the pokemon
    delete p;
}



void UIPokedexInfos::setupTexts() {
    // Fonts
    m_number.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    m_name.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    m_seen.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    m_captured.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    
    // Size
    m_number.setCharacterSize(20);
    m_name.setCharacterSize(24);
    m_seen.setCharacterSize(20);
    m_captured.setCharacterSize(20);
    
    // Colors
    m_number.setFillColor(sf::Color::Black);
    m_name.setFillColor(sf::Color::Black);
    m_seen.setFillColor(sf::Color::Black);
    m_captured.setFillColor(sf::Color::Black);
}
