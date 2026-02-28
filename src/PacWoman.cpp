#include "PacWoman/PacWoman.hpp"
#include "PacWoman/Maze.hpp"
#include <cmath>

namespace pacwoman {

PacWomanEntity::PacWomanEntity() {
    m_size  = {static_cast<float>(TILE_SIZE) - 2.f,
               static_cast<float>(TILE_SIZE) - 2.f};
    m_speed = PACWOMAN_SPEED;

    m_shape.setRadius((TILE_SIZE - 2.f) / 2.f);
    m_shape.setFillColor(sf::Color::Yellow);
}

void PacWomanEntity::update(float dt) {
    if (!m_animating) return;

    // Simple mouth animation.
    if (m_mouthOpening) {
        m_mouthAngle += m_mouthSpeed * dt;
        if (m_mouthAngle >= 45.f) m_mouthOpening = false;
    } else {
        m_mouthAngle -= m_mouthSpeed * dt;
        if (m_mouthAngle <= 0.f) m_mouthOpening = true;
    }
}

void PacWomanEntity::draw(sf::RenderWindow& window) const {
    sf::CircleShape shape(m_shape);
    shape.setPosition(m_position.x + 1.f, m_position.y + 1.f);
    window.draw(shape);
}

void PacWomanEntity::setDesiredDirection(const sf::Vector2f& dir) {
    m_desiredDirection = dir;
}

void PacWomanEntity::move(float dt, const Maze& maze) {
    // Try desired direction first (allows corner-cutting / buffered turns).
    sf::Vector2f newPos = m_position + m_desiredDirection * m_speed * dt;
    if (!maze.isWall(newPos.x, newPos.y, m_size.x, m_size.y)) {
        m_direction = m_desiredDirection;
    }

    // Move in current direction.
    newPos = m_position + m_direction * m_speed * dt;
    if (!maze.isWall(newPos.x, newPos.y, m_size.x, m_size.y)) {
        m_position = newPos;
    }

    // Tunnel wrap-around.
    if (m_position.x < -m_size.x)
        m_position.x = static_cast<float>(MAP_WIDTH * TILE_SIZE);
    else if (m_position.x > static_cast<float>(MAP_WIDTH * TILE_SIZE))
        m_position.x = -m_size.x;
}

void PacWomanEntity::reset(const sf::Vector2f& startPos) {
    m_position = startPos;
    m_direction = {0.f, 0.f};
    m_desiredDirection = {0.f, 0.f};
    m_mouthAngle = 0.f;
}

} // namespace pacwoman
