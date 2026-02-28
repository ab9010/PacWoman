#pragma once

#include "Entity.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>

namespace pacwoman {

class Maze;

/// Ghost behaviour mode.
enum class GhostMode {
    Chase,       // pursue PacWoman
    Scatter,     // retreat to home corner
    Frightened   // edible after power pellet
};

/// Represents a single ghost with simple AI.
class Ghost : public Entity {
public:
    /// Each ghost has a unique colour / personality.
    enum class Personality { Blinky, Pinky, Inky, Clyde };

    explicit Ghost(Personality personality);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

    void move(float dt, const Maze& maze, const sf::Vector2f& pacwomanPos);
    void reset(const sf::Vector2f& startPos);

    void setMode(GhostMode mode);
    GhostMode getMode() const { return m_mode; }

    Personality getPersonality() const { return m_personality; }
    bool isEaten() const { return m_eaten; }
    void setEaten(bool v) { m_eaten = v; }

private:
    /// Choose the next direction at an intersection.
    sf::Vector2f chooseDirection(const Maze& maze,
                                 const sf::Vector2f& target) const;

    /// Scatter-mode target corner for this ghost.
    sf::Vector2f scatterTarget() const;

    sf::Color ghostColor() const;

    Personality m_personality;
    GhostMode   m_mode = GhostMode::Scatter;
    bool         m_eaten = false;
    sf::RectangleShape m_shape;
};

} // namespace pacwoman
