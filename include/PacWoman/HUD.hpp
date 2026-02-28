#pragma once

#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace pacwoman {

/// Heads-Up Display: score, lives, game-over text, etc.
class HUD {
public:
    HUD();

    /// Must be called once after construction to load the font.
    bool loadFont(const std::string& fontPath);

    void setScore(int score);
    void setLives(int lives);
    void setLevel(int level);

    void drawScore(sf::RenderWindow& window) const;
    void drawLives(sf::RenderWindow& window) const;
    void drawGameOver(sf::RenderWindow& window) const;
    void drawReady(sf::RenderWindow& window) const;

private:
    sf::Font m_font;
    bool     m_fontLoaded = false;
    int      m_score = 0;
    int      m_lives = STARTING_LIVES;
    int      m_level = 1;
};

} // namespace pacwoman
