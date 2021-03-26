#include "FightMenuSelector.hpp"
#include "FightDialog.hpp"
#include "../resources/TextureHolder.hpp"

FightMenuSelector::FightMenuSelector(Context& context) :
sf::Drawable(),
m_choiceSprite(context.getTextureHolder()->getTexture(TextureHolder::ui_fightMenuChoice)),
m_buttonSprite(context.getTextureHolder()->getTexture(TextureHolder::ui_fightMenuButtons)),
m_choice(AttacksFC),
m_isSelected(false)
{
    // Set the sprite position
    m_choiceSprite.setOrigin(-207, -307);
    m_buttonSprite.setOrigin(0, 0);
    updateTextureRect();
}



void FightMenuSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = m_buttonSprite.getTexture();
    target.draw(m_buttonSprite, states);
    
    states.texture = m_choiceSprite.getTexture();
    target.draw(m_choiceSprite, states);
}



void FightMenuSelector::setPosition(sf::Vector2f pos) {
    m_choiceSprite.setPosition(pos);
    m_buttonSprite.setPosition(pos);
}



void FightMenuSelector::updateTextureRect() {
    if(m_choice == FightChoice::AttacksFC)
        m_choiceSprite.setTextureRect(sf::IntRect(0, 0, 387, 227));
    else if(m_choice == FightChoice::BagFC)
        m_choiceSprite.setTextureRect(sf::IntRect(0, 227, 387, 227));
    else if(m_choice == FightChoice::FleeFC)
        m_choiceSprite.setTextureRect(sf::IntRect(0, 454, 387, 227));
    else
        m_choiceSprite.setTextureRect(sf::IntRect(0, 681, 387, 227));
}



void FightMenuSelector::manageEvents(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        // Is Space is pressed, then select
        if(event.key.code == sf::Keyboard::Space)
            m_isSelected = true;
        
        // Is Z, Q, S or D is pressed, change the choice and the textureRect
        if(event.key.code == sf::Keyboard::Z){
            m_choice = AttacksFC;
            updateTextureRect();
            m_isSelected = false;
        }
        else if(event.key.code == sf::Keyboard::Q){
            m_choice = BagFC;
            updateTextureRect();
            m_isSelected = false;
        }
        else if(event.key.code == sf::Keyboard::D){
            m_choice = PokemonsFC;
            updateTextureRect();
            m_isSelected = false;
        }
        else if(event.key.code == sf::Keyboard::S){
            m_choice = FleeFC;
            updateTextureRect();
            m_isSelected = false;
        }
    }
}



void FightMenuSelector::setSelected(bool isSelected) {
    m_isSelected = isSelected;
}



bool FightMenuSelector::isSelected() const {
    return m_isSelected;
}



FightMenuSelector::FightChoice FightMenuSelector::getChoice() const {
    return m_choice;
}



void FightMenuSelector::resetChoice() {
    m_isSelected = false;
    
    // Set back to an attack
    m_choice = FightChoice::AttacksFC;
    
    updateTextureRect();
}
