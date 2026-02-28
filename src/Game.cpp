#include "PacWoman/Game.hpp"
#include <algorithm>

namespace pacwoman {

Game::Game()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PacWoman",
               sf::Style::Titlebar | sf::Style::Close) {
    m_window.setFramerateLimit(FRAMERATE);

    m_hud.loadFont("assets/arial.ttf"); // graceful fallback if not found

    // Create four ghosts with different personalities.
    m_ghosts.emplace_back(Ghost::Personality::Blinky);
    m_ghosts.emplace_back(Ghost::Personality::Pinky);
    m_ghosts.emplace_back(Ghost::Personality::Inky);
    m_ghosts.emplace_back(Ghost::Personality::Clyde);

    resetLevel();
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

// ---------------------------------------------------------------
//  Event handling
// ---------------------------------------------------------------
void Game::processEvents() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (m_state == State::GameOver) {
                // Restart on any key after game over.
                m_score = 0;
                m_lives = STARTING_LIVES;
                m_level = 1;
                m_maze.loadDefault();
                m_state = State::Ready;
                m_readyTimer = 2.f;
                resetLevel();
                return;
            }

            switch (event.key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    m_player.setDesiredDirection({0.f, -1.f});
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    m_player.setDesiredDirection({0.f, 1.f});
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    m_player.setDesiredDirection({-1.f, 0.f});
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    m_player.setDesiredDirection({1.f, 0.f});
                    break;
                case sf::Keyboard::Escape:
                    m_window.close();
                    break;
                default:
                    break;
            }
        }
    }
}

// ---------------------------------------------------------------
//  Update
// ---------------------------------------------------------------
void Game::update(float dt) {
    if (m_state == State::Ready) {
        m_readyTimer -= dt;
        if (m_readyTimer <= 0.f)
            m_state = State::Playing;
        return;
    }

    if (m_state != State::Playing)
        return;

    // Update player.
    m_player.update(dt);
    m_player.move(dt, m_maze);

    // Update ghosts.
    for (auto& ghost : m_ghosts) {
        ghost.update(dt);
        ghost.move(dt, m_maze, m_player.getPosition());
    }

    // Frightened timer.
    if (m_frightenedTimer > 0.f) {
        m_frightenedTimer -= dt;
        if (m_frightenedTimer <= 0.f) {
            for (auto& ghost : m_ghosts)
                ghost.setMode(GhostMode::Chase);
        }
    }

    checkPelletCollision();
    checkGhostCollision();

    // Level complete?
    if (m_maze.remainingPellets() == 0) {
        ++m_level;
        m_maze.loadDefault();
        m_state = State::Ready;
        m_readyTimer = 2.f;
        resetLevel();
    }

    m_hud.setScore(m_score);
    m_hud.setLives(m_lives);
    m_hud.setLevel(m_level);
}

// ---------------------------------------------------------------
//  Render
// ---------------------------------------------------------------
void Game::render() {
    m_window.clear(sf::Color::Black);

    m_maze.draw(m_window);
    m_player.draw(m_window);
    for (const auto& ghost : m_ghosts)
        ghost.draw(m_window);

    m_hud.drawScore(m_window);
    m_hud.drawLives(m_window);

    if (m_state == State::Ready)
        m_hud.drawReady(m_window);
    if (m_state == State::GameOver)
        m_hud.drawGameOver(m_window);

    m_window.display();
}

// ---------------------------------------------------------------
//  Helpers
// ---------------------------------------------------------------
void Game::resetLevel() {
    m_player.reset(m_maze.playerStartPosition());

    auto ghostStarts = m_maze.ghostStartPositions();
    for (std::size_t i = 0; i < m_ghosts.size(); ++i)
        m_ghosts[i].reset(ghostStarts[i]);

    m_frightenedTimer = 0.f;
}

void Game::checkPelletCollision() {
    int col = static_cast<int>(m_player.getPosition().x + (TILE_SIZE - 2) / 2.f)
              / static_cast<int>(TILE_SIZE);
    int row = static_cast<int>(m_player.getPosition().y + (TILE_SIZE - 2) / 2.f)
              / static_cast<int>(TILE_SIZE);

    char tile = m_maze.getTile(col, row);
    if (tile == TILE_PELLET) {
        m_maze.setTile(col, row, TILE_EMPTY);
        m_score += PELLET_SCORE;
    } else if (tile == TILE_POWER_PELLET) {
        m_maze.setTile(col, row, TILE_EMPTY);
        m_score += POWER_PELLET_SCORE;
        activateFrightenedMode();
    }
}

void Game::checkGhostCollision() {
    for (auto& ghost : m_ghosts) {
        if (ghost.isEaten()) continue;

        sf::FloatRect playerBounds = m_player.getBounds();
        sf::FloatRect ghostBounds  = ghost.getBounds();

        // Shrink bounds slightly for more forgiving collision.
        playerBounds.left   += 4.f; playerBounds.top    += 4.f;
        playerBounds.width  -= 8.f; playerBounds.height -= 8.f;

        if (playerBounds.intersects(ghostBounds)) {
            if (ghost.getMode() == GhostMode::Frightened) {
                ghost.setEaten(true);
                m_score += GHOST_EAT_SCORE;
            } else {
                // PacWoman caught!
                --m_lives;
                if (m_lives <= 0) {
                    m_state = State::GameOver;
                } else {
                    m_state = State::Ready;
                    m_readyTimer = 2.f;
                    resetLevel();
                }
                return; // Only one death per frame.
            }
        }
    }
}

void Game::activateFrightenedMode() {
    m_frightenedTimer = POWER_PELLET_DURATION;
    for (auto& ghost : m_ghosts) {
        if (!ghost.isEaten())
            ghost.setMode(GhostMode::Frightened);
    }
}

} // namespace pacwoman
