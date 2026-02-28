#include "PacWoman/Maze.hpp"
#include <algorithm>

namespace pacwoman {

Maze::Maze() {
    m_wallShape.setSize({static_cast<float>(TILE_SIZE),
                         static_cast<float>(TILE_SIZE)});
    m_wallShape.setFillColor(sf::Color(33, 33, 222));

    m_pelletShape.setRadius(2.f);
    m_pelletShape.setFillColor(sf::Color(255, 183, 174));

    m_powerPelletShape.setRadius(6.f);
    m_powerPelletShape.setFillColor(sf::Color(255, 183, 174));

    loadDefault();
}

void Maze::loadDefault() {
    // Classic 28x31 Pac-Man-inspired layout.
    // '#' = wall, '.' = pellet, 'O' = power pellet,
    // ' ' = empty, '-' = ghost house door,
    // 'P' = player start, 'G' = ghost start.
    m_grid = {{
        "############################",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#O####.#####.##.#####.####O#",
        "#.####.#####.##.#####.####.#",
        "#..........................#",
        "#.####.##.########.##.####.#",
        "#.####.##.########.##.####.#",
        "#......##....##....##......#",
        "######.##### ## #####.######",
        "     #.##### ## #####.#     ",
        "     #.##    G     ##.#     ",
        "     #.## ###--### ##.#     ",
        "######.## #  G  # ##.######",
        "      .   # GG  #   .      ",
        "######.## #      # ##.######",
        "     #.## ######## ##.#     ",
        "     #.##          ##.#     ",
        "     #.## ######## ##.#     ",
        "######.## ######## ##.######",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#.####.#####.##.#####.####.#",
        "#O..##.......P .......##..O#",
        "###.##.##.########.##.##.###",
        "###.##.##.########.##.##.###",
        "#......##....##....##......#",
        "#.##########.##.##########.#",
        "#.##########.##.##########.#",
        "#..........................#",
        "############################"
    }};
}

void Maze::draw(sf::RenderWindow& window) const {
    for (int row = 0; row < MAP_HEIGHT; ++row) {
        for (int col = 0; col < MAP_WIDTH; ++col) {
            float px = static_cast<float>(col * TILE_SIZE);
            float py = static_cast<float>(row * TILE_SIZE);

            char tile = getTile(col, row);
            if (tile == TILE_WALL) {
                sf::RectangleShape wall(m_wallShape);
                wall.setPosition(px, py);
                window.draw(wall);
            } else if (tile == TILE_PELLET) {
                sf::CircleShape dot(m_pelletShape);
                dot.setPosition(px + TILE_SIZE / 2.f - 2.f,
                                py + TILE_SIZE / 2.f - 2.f);
                window.draw(dot);
            } else if (tile == TILE_POWER_PELLET) {
                sf::CircleShape big(m_powerPelletShape);
                big.setPosition(px + TILE_SIZE / 2.f - 6.f,
                                py + TILE_SIZE / 2.f - 6.f);
                window.draw(big);
            }
        }
    }
}

char Maze::getTile(int col, int row) const {
    if (row < 0 || row >= MAP_HEIGHT || col < 0 || col >= MAP_WIDTH)
        return TILE_WALL;
    return m_grid[static_cast<std::size_t>(row)]
                 [static_cast<std::size_t>(col)];
}

void Maze::setTile(int col, int row, char value) {
    if (row >= 0 && row < MAP_HEIGHT && col >= 0 && col < MAP_WIDTH)
        m_grid[static_cast<std::size_t>(row)]
              [static_cast<std::size_t>(col)] = value;
}

bool Maze::isWall(float x, float y, float w, float h) const {
    // Check all four corners of the bounding box.
    auto check = [this](float px, float py) {
        int col = static_cast<int>(px) / static_cast<int>(TILE_SIZE);
        int row = static_cast<int>(py) / static_cast<int>(TILE_SIZE);
        char t = getTile(col, row);
        return t == TILE_WALL || t == TILE_GHOST_HOUSE;
    };
    return check(x, y) || check(x + w - 1.f, y) ||
           check(x, y + h - 1.f) || check(x + w - 1.f, y + h - 1.f);
}

int Maze::remainingPellets() const {
    int count = 0;
    for (const auto& row : m_grid)
        count += static_cast<int>(
            std::count(row.begin(), row.end(), TILE_PELLET) +
            std::count(row.begin(), row.end(), TILE_POWER_PELLET));
    return count;
}

sf::Vector2f Maze::playerStartPosition() const {
    for (int row = 0; row < MAP_HEIGHT; ++row)
        for (int col = 0; col < MAP_WIDTH; ++col)
            if (getTile(col, row) == TILE_PLAYER_START)
                return {static_cast<float>(col * TILE_SIZE),
                        static_cast<float>(row * TILE_SIZE)};
    return {14.f * TILE_SIZE, 23.f * TILE_SIZE};
}

std::vector<sf::Vector2f> Maze::ghostStartPositions() const {
    std::vector<sf::Vector2f> positions;
    for (int row = 0; row < MAP_HEIGHT; ++row)
        for (int col = 0; col < MAP_WIDTH; ++col)
            if (getTile(col, row) == TILE_GHOST_START)
                positions.push_back(
                    {static_cast<float>(col * TILE_SIZE),
                     static_cast<float>(row * TILE_SIZE)});
    // Ensure we always have 4 ghost positions.
    while (positions.size() < 4)
        positions.push_back({14.f * TILE_SIZE, 14.f * TILE_SIZE});
    return positions;
}

} // namespace pacwoman
