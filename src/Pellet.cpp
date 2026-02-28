#include "PacWoman/Pellet.hpp"

namespace pacwoman {

Pellet::Pellet(sf::Vector2f position, bool isPower)
    : m_position(position), m_isPower(isPower) {
    if (m_isPower) {
        m_shape.setRadius(6.f);
        m_shape.setFillColor(sf::Color(255, 183, 174));
        m_shape.setPosition(m_position.x + TILE_SIZE / 2.f - 6.f,
                            m_position.y + TILE_SIZE / 2.f - 6.f);
    } else {
        m_shape.setRadius(2.f);
        m_shape.setFillColor(sf::Color(255, 183, 174));
        m_shape.setPosition(m_position.x + TILE_SIZE / 2.f - 2.f,
                            m_position.y + TILE_SIZE / 2.f - 2.f);
    }
}

void Pellet::draw(sf::RenderWindow& window) const {
    if (!m_collected)
        window.draw(m_shape);
}

sf::FloatRect Pellet::getBounds() const {
    return m_shape.getGlobalBounds();
}

} // namespace pacwoman
