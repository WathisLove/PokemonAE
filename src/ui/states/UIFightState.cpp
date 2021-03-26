#include "UIFightState.hpp"
#include "../../Constants.hpp"
#include "../../ItemEnums.hpp"

UIFightState::UIFightState(Context& context, Pokemon* ally, Pokemon* ennemy) :
m_dialog(context),
m_context(context),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_fightBackground)),
m_allyDisplay(context, ally, Team::allied),
m_ennemyDisplay(context, ennemy, Team::ennemy),
m_menuSelector(context),
m_attackSelector(context, ally),
m_currentMenu(FightMenu::FM_None),
m_itemDisplay(context),
m_showItem(false),
m_abilityDisplay(context)
{
    setUIPosition();
}



void UIFightState::update(float dt) {
    // Nothing to do here yet
    // This place is mainly reserved for animating the graphical attributes
}



void UIFightState::handleEvent(sf::Event& event) {
    
    // If the dialog is opened, manage events for it
    if(m_dialog.isActive()){
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Space)
                m_dialog.nextString();
        }
    }
    else{
        // Handle events for the menu
        if(m_currentMenu == FightMenu::FM_MainMenu)
            m_menuSelector.manageEvents(event);
        else if(m_currentMenu == FightMenu::FM_AttackMenu)
            m_attackSelector.manageEvents(event);
    }
}



void UIFightState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    
    target.draw(m_allyDisplay, states);
    
    if(m_showItem)
        target.draw(m_itemDisplay, states);
    else
        target.draw(m_ennemyDisplay, states);
    
    if(m_currentMenu == FightMenu::FM_MainMenu)
        target.draw(m_menuSelector, states);
    else if(m_currentMenu == FightMenu::FM_AttackMenu)
        target.draw(m_attackSelector, states);
    
    // The dialgo only draws if needed
    target.draw(m_dialog);
    target.draw(m_abilityDisplay);
}



void UIFightState::updatePokemonDisplays() {
    m_allyDisplay.update();
    m_ennemyDisplay.update();
}



void UIFightState::replaceEnnemySprite(ItemID id) {
    m_showItem = true;
    
    // Set the item
    Item* item = new Item(id);
    m_itemDisplay.setItem(item);
    delete item;
}



void UIFightState::replaceEnnemySprite() {
    m_showItem = false;
}



void UIFightState::showMainMenu() {
    m_currentMenu = FightMenu::FM_MainMenu;
}



void UIFightState::showAttackMenu() {
    // Unselect the MainMenu
    m_menuSelector.setSelected(false);
    
    m_currentMenu = FightMenu::FM_AttackMenu;
}



void UIFightState::hideMenu() {
    // Unselect the two menus
    m_menuSelector.setSelected(false);
    m_attackSelector.setSelected(false);
    
    m_currentMenu = FightMenu::FM_None;
}



void UIFightState::setAlly(Pokemon* ally) {
    // Update the Pokemon display
    m_allyDisplay.setPokemon(ally);
    
    // Update the Attack Selector for the new ally pokemon
    m_attackSelector.update(ally);
}



void UIFightState::setEnnemy(Pokemon* ennemy) {
    m_ennemyDisplay.setPokemon(ennemy);
}



void UIFightState::addDialog(std::wstring str) {
    addDialog(sf::String(str));
}



void UIFightState::addDialog(sf::String str) {
    m_dialog.addString(str);
    
    m_dialog.setActive(true);
}



void UIFightState::nextDialog() {
    m_dialog.nextString();
}



void UIFightState::showDialog(bool show) {
    m_dialog.setActive(show);
}



bool UIFightState::isShowingDialog() {
    return m_dialog.isActive();
}



FightAttackSelector& UIFightState::getAttackMenu() {
    return m_attackSelector;
}



FightMenuSelector& UIFightState::getMenu() {
    return m_menuSelector;
}



void UIFightState::setPokemonDisplayVisibility(Team team, bool val) {
    if(team == Team::allied)
        m_allyDisplay.setVisibility(val);
    else
        m_ennemyDisplay.setVisibility(val);
}



void UIFightState::showAbilityDisplay(Pokemon* p, Team team) {
    m_abilityDisplay.setDisplayedAbility(p, team);
    m_abilityDisplay.show(true);
}



void UIFightState::hideAbilityDisplay() {
    m_abilityDisplay.show(false);
}



void UIFightState::setUIPosition() {
    // Get the top left corner
    sf::Vector2f topLeft = m_context.getWindowTopLeftCorner();
    
    // Set the position of the graphical elements
    m_background.setPosition(topLeft);
    m_allyDisplay.setPosition(topLeft + sf::Vector2f(245, 178));
    m_ennemyDisplay.setPosition(topLeft + sf::Vector2f(463, 128));
    m_menuSelector.setPosition(topLeft);
    m_attackSelector.setPosition(topLeft + sf::Vector2f(222, 318));
    m_dialog.setPosition(topLeft);
    m_itemDisplay.setPosition(topLeft + sf::Vector2f(500, 190));
    
    // Positions for the Ability
    m_abilityDisplay.setAllyPosition(topLeft + sf::Vector2f(210, 250));
    m_abilityDisplay.setEnnemyPosition(topLeft + sf::Vector2f(480, 200));
}
