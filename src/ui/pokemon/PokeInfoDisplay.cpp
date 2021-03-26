#include "PokeInfoDisplay.hpp"
#include "../../resources/FontHolder.hpp"

PokeInfoDisplay::PokeInfoDisplay(Context& context, Pokemon* p) :
m_context(context){
    setupTexts();
    
    setPokemon(p);
}



void PokeInfoDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_specialAbility, states);
    target.draw(m_specialAbilityDescription, states);
    target.draw(m_pokedexNumber, states);
    target.draw(m_firstTrainer, states);
    target.draw(m_startLevel, states);
    target.draw(m_captureZone, states);
    target.draw(m_captureDate, states);
    target.draw(m_firstNature, states);
    target.draw(m_secondNature, states);
}



void PokeInfoDisplay::setPokemon(Pokemon* p) {
    /* Set the texts according to the pokemon infos
    m_pokedexNumber.setString();
    m_startLevel.setString();
    m_captureZone.setString();
    m_captureDate.setString();
    m_secondNature.setString();
    */
    
    // Get the Pokemon Metadata
    PokemonMetadata& data = p->getMetadata();
    
    m_specialAbility.setString(p->getAbility().getName());
    m_specialAbilityDescription.setString(p->getAbility().getDescription());
    m_startLevel.setString(L"Rencontré au N°" + toWString(data.getCaptureLevel()));
    m_captureZone.setString(L"Provenance : " + data.getCaptureZone());
    m_captureDate.setString(L"Obtenu le " + data.getCaptureDate());
    m_firstTrainer.setString(L"Dresseur d'origine : " + data.getOriginalTrainer());
    
    // Nature
    m_firstNature.setString(p->getNature().toFormattedString());
}



void PokeInfoDisplay::setPosition(sf::Vector2f pos) {
    m_specialAbility.setPosition(pos + sf::Vector2f(0,0));
    m_specialAbilityDescription.setPosition(pos + sf::Vector2f(0,20));
    m_pokedexNumber.setPosition(pos + sf::Vector2f(0,40));
    m_firstTrainer.setPosition(pos + sf::Vector2f(0,60));
    m_startLevel.setPosition(pos + sf::Vector2f(0,80));
    m_captureZone.setPosition(pos + sf::Vector2f(0,100));
    m_captureDate.setPosition(pos + sf::Vector2f(0,120));
    m_firstNature.setPosition(pos + sf::Vector2f(0,140));
    m_secondNature.setPosition(pos + sf::Vector2f(0,160));
}



void PokeInfoDisplay::setupTexts() {
    // Get the font
    const sf::Font& font = m_context.getFontHolder()->getFont(FontHolder::dialogFont);
    
    // Set the Texts
    m_specialAbility = sf::Text("Unknown ability", font, 12);
    m_specialAbilityDescription = sf::Text("Unknown ability description", font, 12);
    m_pokedexNumber = sf::Text("Unknown Pokedex Number", font, 12);
    m_firstTrainer = sf::Text("Unknown", font, 12);
    m_startLevel = sf::Text("Unknown Capture Level", font, 12);
    m_captureZone = sf::Text("Unknown Capture Zone", font, 12);
    m_captureDate = sf::Text("Unknown date", font, 12);
    m_firstNature = sf::Text("Unknown nature", font, 12);
    m_secondNature = sf::Text("Unknown second nature", font, 12);
    
    
    // Set the fill colors
    m_specialAbility.setFillColor(sf::Color::Black);
    m_specialAbilityDescription.setFillColor(sf::Color::Black);
    m_pokedexNumber.setFillColor(sf::Color::Black);
    m_firstTrainer.setFillColor(sf::Color::Black);
    m_startLevel.setFillColor(sf::Color::Black);
    m_captureZone.setFillColor(sf::Color::Black);
    m_captureDate.setFillColor(sf::Color::Black);
    m_firstNature.setFillColor(sf::Color::Black);
    m_secondNature.setFillColor(sf::Color::Black);
}
