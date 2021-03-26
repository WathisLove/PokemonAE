#include "FightAttackSelector.hpp"

FightAttackSelector::FightAttackSelector(Context& context, Pokemon* p) :
sf::Drawable(),
m_isSelected(false),
m_choiceSprite(context.getTextureHolder()->getTexture(TextureHolder::ui_fightAttackChoice)),
m_choice(0){
    // Instanciate the pointers in m_displays
    for(int i = 0; i < 4; i++){
        m_displays.at(i) = new AttackDisplay(context);
    }
    
    update(p);
}



FightAttackSelector::~FightAttackSelector() {
    for(AttackDisplay* ad : m_displays){
        delete ad;
    }
}



bool FightAttackSelector::isSelected() const {
    return m_isSelected;
}



void FightAttackSelector::setSelected(bool isSelected) {
    m_isSelected = isSelected;
}



void FightAttackSelector::update(Pokemon* p) {
    for(AttackDisplay* ad : m_displays){
        ad->update();
    }
    
    // Manage the attacks of the pokemon
    for(int i = 0; i < p->getAttackSet().getNbAttacks(); i++){
        m_displays.at(i)->update(p->getAttackSet().getAttack(i));
    }
    
    // Update the choiceSprite
    updateChoiceSprite();
    
    // Set the number of attacks
    m_nbAttacks = p->getAttackSet().getNbAttacks();
}



void FightAttackSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(AttackDisplay* ad : m_displays){
        ad->draw(target, states);
    }
    
    
    states.texture = m_choiceSprite.getTexture();
    target.draw(m_choiceSprite);
}



int FightAttackSelector::getChoice() const {
    return m_choice;
}



void FightAttackSelector::setPosition(sf::Vector2f pos) {
    m_displays.at(0)->setPosition(pos);
    m_displays.at(1)->setPosition(pos+ sf::Vector2f(200, 0));
    m_displays.at(2)->setPosition(pos+ sf::Vector2f(0, 70));
    m_displays.at(3)->setPosition(pos+ sf::Vector2f(200, 70));
    
    // Set the choice sprite position
    m_choiceSprite.setPosition(pos - sf::Vector2f(21, 17));
}



void FightAttackSelector::manageEvents(sf::Event& event) {
    // If selected
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Space)
            m_isSelected = true;
        
        // Selecting Keys
        if(event.key.code == sf::Keyboard::Z){
            m_choice -= 2;
            if(m_choice < 0) m_choice += 2;
            if(m_choice >= m_nbAttacks) m_choice = 0; // Correct the choice value if the attack does not exist
            updateChoiceSprite();
        }
        if(event.key.code == sf::Keyboard::S){
            m_choice += 2;
            if(m_choice > 4) m_choice = 4;
            if(m_choice >= m_nbAttacks) m_choice = 4; // Correct the choice value if the attack does not exist
            updateChoiceSprite();
        }
        if(event.key.code == sf::Keyboard::D){
            m_choice++;
            if(m_choice > 4) m_choice = 4;
            if(m_choice >= m_nbAttacks) m_choice = 4; // Correct the choice value if the attack does not exist
            updateChoiceSprite();
        }
        if(event.key.code == sf::Keyboard::Q){
            m_choice--;
            if(m_choice < 0) m_choice = 0;
            if(m_choice >= m_nbAttacks) m_choice = m_nbAttacks-1; // Correct the choice value if the attack does not exist
            updateChoiceSprite();
        }
        
    }
}



void FightAttackSelector::updateChoiceSprite() {
    if(m_choice == 0) m_choiceSprite.setTextureRect(sf::IntRect(0, 0, 399, 238));
    else if(m_choice == 1) m_choiceSprite.setTextureRect(sf::IntRect(0, 238, 399, 238));
    else if(m_choice == 2) m_choiceSprite.setTextureRect(sf::IntRect(0, 476, 399, 238));
    else if(m_choice == 3) m_choiceSprite.setTextureRect(sf::IntRect(0, 714, 399, 238));
    else              m_choiceSprite.setTextureRect(sf::IntRect(0, 952, 399, 238));
}



void FightAttackSelector::setChoice(int choice) {
    if(choice < 0 || choice > 4) 
        throw std::string("Can't set selector to choice : ") + toString(choice);
    
    m_choice = choice;   
    updateChoiceSprite();
}
