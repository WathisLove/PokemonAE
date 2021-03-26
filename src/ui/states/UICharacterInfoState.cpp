#include "UICharacterInfoState.hpp"
#include "../../resources/FontHolder.hpp"


UICharacterInfoState::UICharacterInfoState(Context& context, Character* character) :
m_badges(context, character),
m_characterSprite(context.getTextureHolder()->getTexture(TextureHolder::characterFull)),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_characterInfoBackground)),
m_characterName("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16),
m_money("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16),
m_timePlayed("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16),
m_pokemonSaw("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16),
m_pokemonCaptured("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16)
{
    setupUI(context, character);
}



void UICharacterInfoState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    target.draw(m_characterSprite, states);
    target.draw(m_badges, states);
    
    // Draw the Texts
    target.draw(m_characterName, states);
    target.draw(m_money, states);
    target.draw(m_timePlayed, states);
    target.draw(m_pokemonSaw, states);
    target.draw(m_pokemonCaptured, states);
}



void UICharacterInfoState::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    m_characterSprite.setPosition(pos + sf::Vector2f(60, 60));
    m_badges.setPosition(pos + sf::Vector2f(80, 320));
    
    // Texts' positions
    m_characterName.setPosition(pos + sf::Vector2f(400, 60));
    m_money.setPosition(pos + sf::Vector2f(400, 130));
    m_timePlayed.setPosition(pos + sf::Vector2f(400, 200));
    m_pokemonSaw.setPosition(pos + sf::Vector2f(740, 110));
    m_pokemonCaptured.setPosition(pos + sf::Vector2f(740, 180));
}



void UICharacterInfoState::setupUI(Context& context, Character* character) {
    // Set the Character Sprite scale
    m_characterSprite.setScale(0.5, 0.5);
    
    // Setup the Texts
    setupTexts(context, character);
}



void UICharacterInfoState::setupTexts(Context& context, Character* character) {
    // Set the Colors
    m_characterName.setFillColor(sf::Color::Black);
    m_money.setFillColor(sf::Color::Black);
    m_timePlayed.setFillColor(sf::Color::Black);
    m_pokemonSaw.setFillColor(sf::Color::Black);
    m_pokemonCaptured.setFillColor(sf::Color::Black);
    
    // Set the Strings
    m_characterName.setString(character->getName());
    m_money.setString(toString(character->getMoney()) + " $");
    m_timePlayed.setString(character->getTimePlayed());
    m_pokemonSaw.setString(toString(character->getPokedex().getTotalSaw()));
    m_pokemonCaptured.setString(toString(character->getPokedex().getTotalCaptured()));
}
