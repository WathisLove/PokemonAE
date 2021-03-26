#include "ZoneDialog.hpp"
#include "SFML/Graphics/Rect.hpp"


ZoneDialog::ZoneDialog(sf::String* string, int x, int y, int width, int height) :
m_string(string),
m_rect(x, y, width, height){

}



ZoneDialog::~ZoneDialog() {
    delete m_string;
}



const sf::String& ZoneDialog::getDialog() const {
    return *m_string;
}



bool ZoneDialog::occupies(sf::Vector2i pos) const {
    return !(pos.x < m_rect.left 
            || pos.y < m_rect.top 
            || pos.x > m_rect.left + m_rect.width
            || pos.y > m_rect.top + m_rect.height);
}
