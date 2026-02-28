#pragma once

namespace pacwoman {

// Window settings
constexpr unsigned int WINDOW_WIDTH  = 672;   // 28 tiles * 24 pixels
constexpr unsigned int WINDOW_HEIGHT = 774;   // 31 tiles * 24 pixels + 30 for HUD
constexpr unsigned int TILE_SIZE     = 24;
constexpr unsigned int FRAMERATE     = 60;

// Map dimensions (in tiles)
constexpr int MAP_WIDTH  = 28;
constexpr int MAP_HEIGHT = 31;

// Gameplay
constexpr float PACWOMAN_SPEED      = 120.f;  // pixels per second
constexpr float GHOST_SPEED         = 100.f;
constexpr float GHOST_FRIGHTENED_SPEED = 60.f;
constexpr int   PELLET_SCORE        = 10;
constexpr int   POWER_PELLET_SCORE  = 50;
constexpr int   GHOST_EAT_SCORE     = 200;
constexpr int   STARTING_LIVES      = 3;
constexpr float POWER_PELLET_DURATION = 8.f;  // seconds

// Tile types in the map
constexpr char TILE_WALL         = '#';
constexpr char TILE_EMPTY        = ' ';
constexpr char TILE_PELLET       = '.';
constexpr char TILE_POWER_PELLET = 'O';
constexpr char TILE_GHOST_HOUSE  = '-';
constexpr char TILE_PLAYER_START = 'P';
constexpr char TILE_GHOST_START  = 'G';

} // namespace pacwoman
