#pragma once

#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>

namespace pacwoman {

/// Tile-based maze that defines walls, pellets, and open paths.
class Maze {
public:
    Maze();

    /// Load the default built-in level layout.
    void loadDefault();

    /// Draw the maze (walls, pellets, power pellets).
    void draw(sf::RenderWindow& window) const;

    /// Returns the tile character at tile coordinates (col, row).
    char getTile(int col, int row) const;

    /// Set the tile at tile coordinates.
    void setTile(int col, int row, char value);

    /// Check whether a world-position bounding box collides with a wall.
    bool isWall(float x, float y, float width, float height) const;

    /// Count remaining pellets (normal + power).
    int remainingPellets() const;

    /// Pixel position of the player start tile.
    sf::Vector2f playerStartPosition() const;

    /// Pixel positions of the ghost start tiles.
    std::vector<sf::Vector2f> ghostStartPositions() const;

private:
    std::array<std::string, MAP_HEIGHT> m_grid;
    sf::RectangleShape m_wallShape;
    sf::CircleShape m_pelletShape;
    sf::CircleShape m_powerPelletShape;
};

} // namespace pacwoman
