#pragma once

#include "Maze.hpp"
#include "PacWoman.hpp"
#include "Ghost.hpp"
#include "HUD.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace pacwoman {

/// Top-level game class that owns the window, game loop, and all entities.
class Game {
public:
    Game();

    /// Run the main game loop (blocking).
    void run();

private:
    // ----- loop phases -----
    void processEvents();
    void update(float dt);
    void render();

    // ----- helpers -----
    void resetLevel();
    void checkPelletCollision();
    void checkGhostCollision();
    void activateFrightenedMode();

    // ----- state -----
    enum class State { Ready, Playing, GameOver };

    sf::RenderWindow m_window;
    State            m_state = State::Ready;
    float            m_readyTimer = 2.f;

    Maze             m_maze;
    PacWomanEntity   m_player;
    std::vector<Ghost> m_ghosts;
    HUD              m_hud;

    int   m_score = 0;
    int   m_lives = STARTING_LIVES;
    int   m_level = 1;

    float m_frightenedTimer = 0.f;
};

} // namespace pacwoman
