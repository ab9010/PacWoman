#include "PacWoman/Ghost.hpp"
#include "PacWoman/Maze.hpp"
#include <cmath>
#include <limits>

namespace pacwoman {

Ghost::Ghost(Personality personality)
    : m_personality(personality) {
    m_size  = {static_cast<float>(TILE_SIZE) - 2.f,
               static_cast<float>(TILE_SIZE) - 2.f};
    m_speed = GHOST_SPEED;

    m_shape.setSize(m_size);
    m_shape.setFillColor(ghostColor());
}

void Ghost::update(float /*dt*/) {
    // Visual updates (e.g., eye direction) can be added here.
}

void Ghost::draw(sf::RenderWindow& window) const {
    sf::RectangleShape shape(m_shape);
    shape.setPosition(m_position.x + 1.f, m_position.y + 1.f);

    if (m_mode == GhostMode::Frightened && !m_eaten) {
        shape.setFillColor(sf::Color(33, 33, 255));
    } else if (m_eaten) {
        shape.setFillColor(sf::Color(200, 200, 200, 100));
    } else {
        shape.setFillColor(ghostColor());
    }

    window.draw(shape);
}

void Ghost::move(float dt, const Maze& maze,
                 const sf::Vector2f& pacwomanPos) {
    float spd = (m_mode == GhostMode::Frightened)
                    ? GHOST_FRIGHTENED_SPEED
                    : m_speed;

    sf::Vector2f target;
    switch (m_mode) {
        case GhostMode::Chase:
            target = pacwomanPos; // Blinky-style: direct chase.
            break;
        case GhostMode::Scatter:
            target = scatterTarget();
            break;
        case GhostMode::Frightened:
            // Random-ish: just continue current direction or scatter.
            target = scatterTarget();
            break;
    }

    // At every tile boundary, pick a new direction.
    int tileX = static_cast<int>(m_position.x + m_size.x / 2.f)
                / static_cast<int>(TILE_SIZE);
    int tileY = static_cast<int>(m_position.y + m_size.y / 2.f)
                / static_cast<int>(TILE_SIZE);
    float tileCenterX = tileX * static_cast<float>(TILE_SIZE);
    float tileCenterY = tileY * static_cast<float>(TILE_SIZE);

    float distToCenter = std::abs(m_position.x - tileCenterX)
                       + std::abs(m_position.y - tileCenterY);

    if (distToCenter < 2.f) {
        m_direction = chooseDirection(maze, target);
    }

    sf::Vector2f newPos = m_position + m_direction * spd * dt;
    if (!maze.isWall(newPos.x, newPos.y, m_size.x, m_size.y)) {
        m_position = newPos;
    } else {
        // If stuck, try to pick a new direction now.
        m_direction = chooseDirection(maze, target);
    }

    // Tunnel wrap-around.
    if (m_position.x < -m_size.x)
        m_position.x = static_cast<float>(MAP_WIDTH * TILE_SIZE);
    else if (m_position.x > static_cast<float>(MAP_WIDTH * TILE_SIZE))
        m_position.x = -m_size.x;
}

void Ghost::reset(const sf::Vector2f& startPos) {
    m_position = startPos;
    m_direction = {0.f, -1.f};
    m_mode = GhostMode::Scatter;
    m_eaten = false;
    m_shape.setFillColor(ghostColor());
}

void Ghost::setMode(GhostMode mode) {
    // Reverse direction when switching between Chase/Scatter.
    if ((m_mode == GhostMode::Chase && mode == GhostMode::Scatter) ||
        (m_mode == GhostMode::Scatter && mode == GhostMode::Chase)) {
        m_direction = -m_direction;
    }
    m_mode = mode;
}

sf::Vector2f Ghost::chooseDirection(const Maze& maze,
                                     const sf::Vector2f& target) const {
    // Try all four cardinal directions, pick the one closest to target.
    const sf::Vector2f dirs[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    sf::Vector2f best = m_direction;
    float bestDist = std::numeric_limits<float>::max();

    for (const auto& d : dirs) {
        // Ghosts cannot reverse direction (skip when already moving).
        if (m_direction.x != 0.f || m_direction.y != 0.f) {
            if (d.x == -m_direction.x && d.y == -m_direction.y)
                continue;
        }

        sf::Vector2f testPos = m_position + d * static_cast<float>(TILE_SIZE);
        if (maze.isWall(testPos.x, testPos.y, m_size.x, m_size.y))
            continue;

        float dx = testPos.x - target.x;
        float dy = testPos.y - target.y;
        float dist = dx * dx + dy * dy; // squared distance is fine

        if (dist < bestDist) {
            bestDist = dist;
            best = d;
        }
    }
    return best;
}

sf::Vector2f Ghost::scatterTarget() const {
    float w = static_cast<float>(MAP_WIDTH * TILE_SIZE);
    float h = static_cast<float>(MAP_HEIGHT * TILE_SIZE);
    switch (m_personality) {
        case Personality::Blinky: return {w, 0.f};
        case Personality::Pinky:  return {0.f, 0.f};
        case Personality::Inky:   return {w, h};
        case Personality::Clyde:  return {0.f, h};
    }
    return {0.f, 0.f};
}

sf::Color Ghost::ghostColor() const {
    switch (m_personality) {
        case Personality::Blinky: return sf::Color::Red;
        case Personality::Pinky:  return sf::Color(255, 184, 255);
        case Personality::Inky:   return sf::Color::Cyan;
        case Personality::Clyde:  return sf::Color(255, 184, 82);
    }
    return sf::Color::White;
}

} // namespace pacwoman
