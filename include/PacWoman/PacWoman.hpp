#pragma once

#include "Entity.hpp"
#include "Constants.hpp"

namespace pacwoman {

class Maze;

/// The player-controlled character.
class PacWomanEntity : public Entity {
public:
    PacWomanEntity();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

    /// Attempt to change direction; the actual turn happens on the next
    /// aligned tile so the player can "buffer" turns.
    void setDesiredDirection(const sf::Vector2f& dir);

    /// Apply movement, checking wall collisions with the maze.
    void move(float dt, const Maze& maze);

    /// Reset to starting position/direction.
    void reset(const sf::Vector2f& startPos);

    /// Animation helpers.
    void setAnimating(bool v) { m_animating = v; }

private:
    sf::Vector2f m_desiredDirection{0.f, 0.f};
    sf::CircleShape m_shape;
    float m_mouthAngle = 0.f;
    float m_mouthSpeed = 300.f;
    bool  m_mouthOpening = true;
    bool  m_animating = true;
};

} // namespace pacwoman
