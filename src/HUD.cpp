#include "PacWoman/HUD.hpp"
#include <sstream>

namespace pacwoman {

HUD::HUD() = default;

bool HUD::loadFont(const std::string& fontPath) {
    m_fontLoaded = m_font.loadFromFile(fontPath);
    return m_fontLoaded;
}

void HUD::setScore(int score) { m_score = score; }
void HUD::setLives(int lives) { m_lives = lives; }
void HUD::setLevel(int level) { m_level = level; }

void HUD::drawScore(sf::RenderWindow& window) const {
    if (!m_fontLoaded) return;

    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);

    std::ostringstream ss;
    ss << "Score: " << m_score << "   Level: " << m_level;
    text.setString(ss.str());
    text.setPosition(10.f, static_cast<float>(MAP_HEIGHT * TILE_SIZE) + 2.f);

    window.draw(text);
}

void HUD::drawLives(sf::RenderWindow& window) const {
    // Draw small yellow circles for remaining lives.
    for (int i = 0; i < m_lives; ++i) {
        sf::CircleShape life(8.f);
        life.setFillColor(sf::Color::Yellow);
        life.setPosition(static_cast<float>(WINDOW_WIDTH - 30 * (i + 1)),
                         static_cast<float>(MAP_HEIGHT * TILE_SIZE) + 4.f);
        window.draw(life);
    }
}

void HUD::drawGameOver(sf::RenderWindow& window) const {
    if (!m_fontLoaded) return;

    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::Red);
    text.setString("GAME OVER");
    sf::FloatRect bounds = text.getLocalBounds();
    text.setPosition((WINDOW_WIDTH - bounds.width) / 2.f,
                     (WINDOW_HEIGHT - bounds.height) / 2.f);
    window.draw(text);
}

void HUD::drawReady(sf::RenderWindow& window) const {
    if (!m_fontLoaded) return;

    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setString("READY!");
    sf::FloatRect bounds = text.getLocalBounds();
    text.setPosition((WINDOW_WIDTH - bounds.width) / 2.f,
                     (WINDOW_HEIGHT - bounds.height) / 2.f);
    window.draw(text);
}

} // namespace pacwoman
