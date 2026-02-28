#pragma once

#include <SFML/Graphics.hpp>

namespace pacwoman {

/// Base class for all movable game entities.
class Entity {
public:
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    sf::Vector2f getPosition() const { return m_position; }
    void setPosition(const sf::Vector2f& pos) { m_position = pos; }

    sf::Vector2f getDirection() const { return m_direction; }
    void setDirection(const sf::Vector2f& dir) { m_direction = dir; }

    /// Returns the bounding rectangle for collision detection.
    sf::FloatRect getBounds() const {
        return {m_position.x, m_position.y, m_size.x, m_size.y};
    }

protected:
    sf::Vector2f m_position{0.f, 0.f};
    sf::Vector2f m_direction{0.f, 0.f};
    sf::Vector2f m_size{0.f, 0.f};
    float m_speed = 0.f;
};

} // namespace pacwoman
