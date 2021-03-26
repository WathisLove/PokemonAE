#include "UILearnAttackState.hpp"
#include "../../pokemons/attacks/AttackFabric.hpp"

#include "../../resources/FontHolder.hpp"
#include "../../resources/TextureHolder.hpp"

UILearnAttackState::UILearnAttackState(Context& context, Pokemon* pokemon, AttackID attackLearning) :
m_context(context),
m_pokemon(pokemon),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_teamInfo)),
m_attacksDisplay(context, pokemon),
m_learnAttackDisplay(context),
m_pokemonDisplay(context, pokemon, Team::ennemy),
m_firstType(context, pokemon->getType().getFirstType()),
m_secondType(context, pokemon->getType().getSecondType()),
m_cursor(context.getTextureHolder()->getTexture(TextureHolder::ui_attackCursor)),
m_sexDisplay(context, pokemon->getSex())
{
    // Setup the Texts
    setupTexts();
    
    // Set the Display attack
    m_learningAttack = AttackFabric::createAttack(attackLearning);
    m_learnAttackDisplay.update(m_learningAttack);
    
    // Select the first attack
    selectAttack(0);
    
    // Set the scale of the pokemon display
    m_pokemonDisplay.setZoomFactor(1.5);
}



UILearnAttackState::~UILearnAttackState() {
    delete m_learningAttack;
}



void UILearnAttackState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the Background
    target.draw(m_background, states);

    // Draw the other elements
    target.draw(m_pokemonDisplay, states);
    target.draw(m_firstType, states);
    target.draw(m_secondType, states);
    
    target.draw(m_sexDisplay, states);
    target.draw(m_nameText, states);
    target.draw(m_levelText, states);
    
    // Draw the texts
    for(int i = 0; i < m_statLabels.size(); i++){
        target.draw(m_statLabels.at(i), states);
        target.draw(m_statValues.at(i), states);
    }
    
    target.draw(m_attacksDisplay, states);
    target.draw(m_learnAttackDisplay, states);
    
    target.draw(m_attackPower, states);
    target.draw(m_attackDescription, states);
    
    // Draw the cursor over the other parts
    target.draw(m_cursor, states);
}



void UILearnAttackState::selectAttack(int attackNum) {
    // Get the position for the first attack
    sf::Vector2f firstAttackPos = m_background.getPosition() + sf::Vector2f(400, 120);
    
    if(attackNum < 4){
        // Set the cursor for the Vertical Display
        m_cursor.setPosition(firstAttackPos + sf::Vector2f(-2, -2 + attackNum * 64));
    
        // Update the Texts
        m_attackDescription.setString(m_pokemon->getAttackSet().getAttack(attackNum)->getDescription());
        m_attackPower.setString(toString(m_pokemon->getAttackSet().getAttack(attackNum)->getDamage()));
    }
    else{
        // Set the cursor for the new Attack
        m_cursor.setPosition(m_learnAttackDisplay.getPosition() + sf::Vector2f(-2, -2));
    
        // Update the Texts
        m_attackDescription.setString(m_learningAttack->getDescription());
        m_attackPower.setString(toString(m_learningAttack->getDamage()));
    }
    
}



void UILearnAttackState::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    m_pokemonDisplay.setPosition(pos + sf::Vector2f(60, 40));
    m_firstType.setPosition(pos + sf::Vector2f(200, 100));
    m_secondType.setPosition(pos + sf::Vector2f(260, 100));
    
    m_sexDisplay.setPosition(pos + sf::Vector2f(50, 200));
    m_nameText.setPosition(pos + sf::Vector2f(80, 190));
    
    m_levelText.setPosition(pos + sf::Vector2f(110, 220));
    
    m_attacksDisplay.setPosition(pos + sf::Vector2f(400, 120));
    m_learnAttackDisplay.setPosition(pos + sf::Vector2f(400, 400));
    
    m_attackPower.setPosition(pos + sf::Vector2f(440, 500));
    m_attackDescription.setPosition(pos + sf::Vector2f(400, 540));
    
    for(int i = 0; i < m_statLabels.size(); i++){
        // Set the fonts and colors for the arrays
        m_statLabels.at(i).setPosition(pos + sf::Vector2f(60, 400 + 30 * i));
        m_statValues.at(i).setPosition(pos + sf::Vector2f(180, 400 + 30 * i));
    }
    
    // Move the cursor to the first attack
    selectAttack(0);
}



void UILearnAttackState::setupTexts() {
    // Set the Fonts
    for(int i = 0; i < m_statLabels.size(); i++){
        // Set the fonts and colors for the arrays
        m_statLabels.at(i).setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
        m_statLabels.at(i).setCharacterSize(20);
        m_statLabels.at(i).setFillColor(sf::Color::Black);
        
        m_statValues.at(i).setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
        m_statValues.at(i).setCharacterSize(20);
        m_statValues.at(i).setFillColor(sf::Color::Black);
    }
    
    // Fonts and color for the other texts
    m_nameText.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    m_nameText.setCharacterSize(22);
    m_nameText.setFillColor(sf::Color::Black);
    
    m_levelText.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    m_levelText.setCharacterSize(20);
    m_levelText.setFillColor(sf::Color::Black);
    
    m_attackPower.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    m_attackPower.setCharacterSize(20);
    m_attackPower.setFillColor(sf::Color::Black);
    
    m_attackDescription.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    m_attackDescription.setCharacterSize(16);
    m_attackDescription.setFillColor(sf::Color::Black);
    
    
    ///===/// Text Content ///===///
    m_nameText.setString(m_pokemon->getName());
    m_levelText.setString(L"N° " + toWString(m_pokemon->getLevel()));
    
    // Set the Labels
    m_statLabels[0].setString("Attaque");
    m_statLabels[1].setString("Defense");
    m_statLabels[2].setString(L"Attaque Spé.");
    m_statLabels[3].setString(L"Défense Spé.");
    m_statLabels[4].setString("Vitesse");
    
    // Set the values
    m_statValues[0].setString(toString(m_pokemon->getStatValue(StatName::attack)));
    m_statValues[1].setString(toString(m_pokemon->getStatValue(StatName::defense)));
    m_statValues[2].setString(toString(m_pokemon->getStatValue(StatName::special_attack)));
    m_statValues[3].setString(toString(m_pokemon->getStatValue(StatName::special_defense)));
    m_statValues[4].setString(toString(m_pokemon->getStatValue(StatName::speed)));
}
