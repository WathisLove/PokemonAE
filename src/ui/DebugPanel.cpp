#include "DebugPanel.hpp"
#include "../resources/FontHolder.hpp"

DebugPanel::DebugPanel(Context& context) :
m_text("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16),
m_show(false)
{
    m_text.setFillColor(sf::Color::White);
    m_text.setString("R : Toggle Running \n"
                    "F1 : Debug Keys    F2 : Stack Messages \nF3 : Heal Team \nF4 : Level Up \n"
                    "F5 : Toggle Music    F6 : Freeze Character    F7 : Unfreeze Character\nF9 : Show Character Infos \nF10 : Game Speed \n"
                    "F11 : Screenshot \nF12 : Restart Game"
                    "\n- Fight -\nF7 : Close Fight \n+ : Ennemy 1 HP \n- : Ally 1 HP");
}



void DebugPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_show)
        target.draw(m_text, states);
}



void DebugPanel::toggleDisplay() {
    m_show = !m_show;
}



void DebugPanel::setPosition(sf::Vector2f pos) {
    m_text.setPosition(pos);
}