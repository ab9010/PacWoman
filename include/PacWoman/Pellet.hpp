#pragma once

#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace pacwoman {

/// Simple pellet manager (drawn by the Maze, but collected via Game logic).
/// This header is kept for potential future expansion (fruit items, etc.).
class Pellet {
public:
    Pellet(sf::Vector2f position, bool isPower);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

    bool isPowerPellet() const { return m_isPower; }
    bool isCollected() const  { return m_collected; }
    void collect()            { m_collected = true; }

private:
    sf::Vector2f  m_position;
    bool          m_isPower   = false;
    bool          m_collected = false;
    sf::CircleShape m_shape;
};

} // namespace pacwoman
